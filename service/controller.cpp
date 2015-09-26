#include "controller.h"

#include <QDebug>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QScopedPointer>
#include <QDebug>

#include "usb/icharger_usb.h"
#include "usb/hotplug_adapter.h"
#include "usb/eventhandler.h"

#include "nzmqt/nzmqt.hpp"
#include "zmq/zmq_publisher.h"

#include "bonjour/bonjourserviceregister.h"

//Q_LOGGING_CATEGORY(controller, "controller")

using namespace nzmqt;
using namespace std;

Controller::Controller(QObject *parent) : QObject(parent), 
    _ctx(0),
    _pub(0), 
    _hotplug(0),
    _hotplug_handler(0),
    _hotplug_thread(0),
    _registry(0)
{
}

Controller::~Controller() {
    delete _registry;
    _registry = 0;
    
    _hotplug_handler->killTimer(_hotplug_handler->timer);
    _hotplug_handler->deleteLater();
    _hotplug_handler = 0;
    
    _hotplug_thread->quit();
    _hotplug_thread->deleteLater();    
    _hotplug_thread = 0;
    
    delete _pub;
    _pub = 0;

    delete _bon;
    _bon = 0;

    _ctx->stop();
    delete _ctx;
    _ctx = 0;
}

int Controller::init() {
    try {
        // ZeroMQ to send / receive messages - requires a context.
        _ctx = createDefaultContext(this);
        _ctx->start();
        
        // Get the message infrastructure ready (pub/sub and messaging).
        _pub = new ZMQ_Publisher(_ctx);
        
        // Bonjour system needs to publish our ZMQ publisher port
        _bon = new BonjourServiceRegister;
        
        // Respond to changes to the publisher port
        connect(_pub, SIGNAL(port_changed(int)), 
                this, SLOT(register_pub_port(int)));
        
        // TODO: Respond to changes to the messaging port. 
        
        // bind the publisher to cause it to find a local ephemeral port and publish it
        if(!_pub->bind()) {
            qCritical() << "unable to bind the zmq publisher to its interface";
            return 1;
        }
        
        // Kick off a listener for USB hotplug events - so we keep our device list fresh
        _hotplug = new HotplugEventAdapter(_usb.ctx);
        QObject::connect(_hotplug, SIGNAL(hotplug_event(bool, libusb_device*, int, int, int)), 
                         this, SLOT(notify_hotplug_event(bool, libusb_device*, int, int, int)));
    
        // Primitive libsusb event handler.
        _hotplug_handler = new UseQtEventDriver(_usb.ctx);
        _hotplug_thread = new QThread();
        _hotplug_handler->moveToThread(_hotplug_thread);
        _hotplug_thread->start();
        
        return 0;
    }
    
    catch(zmq::error_t& ex) {
        qCritical()<< "failed to init zmq:" << ex.what();
        return 1;
    }
}

void Controller::register_pub_port(int new_port) {
    _bon->registerService("_charger-service-pub._tcp", new_port);   
    qCritical() << "pub/sub comms are being made on port number:" << new_port;
}

void Controller::notify_hotplug_event(bool added, libusb_device* dev, int vendor, int product, int sn_idx)  {
    libusb_device_handle* handle = 0;
    int r = libusb_open(dev, &handle);
    if(!r) {
        qCritical() << "unable to open the device in order to get its serial number";
        return;
    }
   
    unsigned char serial_number[256];
    memset(serial_number, 0, sizeof(serial_number));
    r = libusb_get_descriptor(handle, LIBUSB_DT_STRING, sn_idx, serial_number, sizeof(serial_number) - 1);
    libusb_close(handle);

    if(r != 0) {
        qCritical() << "unable to obtain serial number of device";
        return;
    }

    QString sn = QString::fromLatin1((const char *)serial_number);
    
    qInfo() << "a usb hotplug event occured, vendor:" << vendor << ", product:" << product << ", serial number:" << sn;
    if(added)
        _registry->activate_device(dev, vendor, product, sn);
    else
        _registry->deactivate_device(dev, vendor, product, sn);
    
}
