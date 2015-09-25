#include "controller.h"

#include <QDebug>
#include <QThread>
#include <QStringList>
#include <QScopedPointer>
#include <QDebug>

#include <QDebug>

#include "usb/icharger_usb.h"
#include "usb/hotplug_adapter.h"
#include "usb/eventhandler.h"

#include "nzmqt/nzmqt.hpp"
#include "zmq/zmq_publisher.h"

#include "bonjour/bonjourserviceregister.h"

using namespace nzmqt;

Controller::Controller(QObject *parent) : QObject(parent), 
    _ctx(0),
    _pub(0), 
    _hotplug(0),
    _hotplug_handler(0),
    _hotplug_thread(0)
{
}

Controller::~Controller() {
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
    // ZeroMQ to send / receive messages - requires a context.
    _ctx = createDefaultContext();
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
    _pub->bind();
    
    // Kick off a listener for USB hotplug events - so we keep our device list fresh
    _hotplug = new HotplugEventAdapter(_usb.ctx);
    QObject::connect(_hotplug, SIGNAL(hotplug_event(bool)), 
                     this, SLOT(notify_hotplug_event(bool)));

    // Primitive libsusb event handler.
    _hotplug_handler = new UseQtEventDriver(_usb.ctx);
    _hotplug_thread = new QThread();
    _hotplug_handler->moveToThread(_hotplug_thread);
    _hotplug_thread->start();
    
    return 0;
}

void Controller::register_pub_port(int new_port) {
    _bon->registerService("_charger-service-pub._tcp", new_port);   
}

void Controller::notify_hotplug_event(bool added)  {
    qDebug() << "a device was added:" << added;
}
