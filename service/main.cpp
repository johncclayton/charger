#include <QCoreApplication>
#include <QThread>
#include <QStringList>
#include <QScopedPointer>
#include <QDebug>

#include "usb/icharger_usb.h"
#include "usb/usb_hotpluglistener.h"
#include "usb/eventhandler.h"

#include "nzmqt/nzmqt.hpp"
#include "zmq/zmq_publisher.h"

#include "bonjour/bonjourserviceregister.h"

using namespace nzmqt;

// The app will run as a daemon process, accepting requests to do stuff via ZeroMQ.  These requests are 
// simply passed into the USB device that represents the charger. 
//
// Current status of the device, it's channels and so on is published continuously on the ZeroMQ pub/sub
// bus.
// 
// ALL configuration is via Bonjour - the app will publish its services there. 

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

    usb_context c;
    if(!c) {
        qDebug() << "failed to init the USB context, cannot start up";
        return -1;
    }
    
    int rc = 0;
    
    {
        // ZeroMQ to send / receive messages - requires a context.
        QScopedPointer<ZMQContext> context;
        context.reset(createDefaultContext());
        context->start();
        
        // Get the message infrastructure ready (pub/sub and messaging).
        ZMQ_Publisher* pub = new ZMQ_Publisher(context.data());
        
        // Bonjour system needs to publish our ZMQ publisher port
        BonjourServiceRegister* bon = new BonjourServiceRegister;
        
        // Respond to changes to the publisher port
        QObject::connect(pub, &ZMQ_Publisher::port_changed, [=](int port) {
            bon->registerService("_charger-service-pub._tcp", port);
        });
        
        // TODO: Respond to changes to the messaging port. 
        
        // bind the publisher to cause it to find a local ephemeral port and publish it
        pub->bind();
        
        // Kick off a listener for USB hotplug events - so we keep our device list fresh
        QSharedPointer<USB_HotPlugListener> usb_listen(new USB_HotPlugListener(c.ctx));
        QObject::connect(usb_listen.data(), &USB_HotPlugListener::hotplug_event, [=](bool added) {
            qDebug() << "a device was added:" << added;
        });

        // Primitive libsusb event handler.
        EventHandler* handler = new EventHandler(c.ctx);
        QThread* handlerThread = new QThread();
        handler->moveToThread(handlerThread);
        handlerThread->start();
        
        Destroyer handlerShutdown(handlerThread, handler);
                        
        rc = app.exec();
    }
    
    return rc;
}
