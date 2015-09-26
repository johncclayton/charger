#include "app_controller.h"

#include <QtGlobal>
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
#include "zmq/publisher.h"

#include "bonjour/bonjourserviceregister.h"

//Q_LOGGING_CATEGORY(controller, "controller")

using namespace nzmqt;
using namespace std;

AppController::AppController(QObject *parent) : QObject(parent), 
    _ctx(0),
    _pub(0), 
    _hotplug(0),
    _hotplug_handler(0),
    _hotplug_thread(0),
    _registry(0),
    _msg_handler(0)
{
}

AppController::~AppController() {
    delete _msg_handler;
    _msg_handler = 0;
            
    delete _registry;
    _registry = 0;
    
    _hotplug_handler->killTimer(_hotplug_handler->timer);
    _hotplug_handler->deleteLater();
    _hotplug_handler = 0;
    
    _hotplug_thread->quit();
    _hotplug_thread->deleteLater();    
    _hotplug_thread = 0;
    
    delete _bon;
    _bon = 0;
    
    _ctx->stop();
    delete _ctx;
    _ctx = 0;
}

int AppController::init() {
    try {
        // ZeroMQ to send / receive messages - requires a context.
        _ctx = createDefaultContext(this);
        _ctx->start();
        
        // Get the message infrastructure ready (pub/sub and messaging).
        _pub = Publisher_ptr(new Publisher(_ctx));
        
        // Bonjour system needs to publish our ZMQ publisher port
        _bon = new BonjourServiceRegister;

        _registry = new DeviceRegistry(_usb.ctx, _pub);
        
        QObject::connect(_registry, SIGNAL(device_activated(QString)),
                         this, SLOT(device_added(QString)));
        QObject::connect(_registry, SIGNAL(device_deactivated(QString)),
                         this, SLOT(device_removed(QString)));
               
        // Respond to changes to the publisher port
        connect(_pub.data(), SIGNAL(port_changed(int)), 
                this, SLOT(register_pub_port(int)));
                
        // bind the publisher to cause it to find a local ephemeral port and publish it
        if(!_pub->bind()) {
            qDebug() << "unable to bind the zmq publisher to its interface";
            return 1;
        }
        
        _msg_handler = new MessageHandler(_ctx);
        connect(_msg_handler, SIGNAL(port_changed(int)),
                this, SLOT(register_msg_port(int)));
        
        if(!_msg_handler->bind()) {
            qDebug() << "unable to bind the zmq message handler to its interface";
            return 2;
        }
        
        // Kick off a listener for USB hotplug events - so we keep our device list fresh
        _hotplug = new HotplugEventAdapter();
        QObject::connect(_hotplug, SIGNAL(hotplug_event(bool, int, int, QString)), 
                         this, SLOT(notify_hotplug_event(bool, int, int, QString)));
        
        // Primitive libsusb event handler.
        _hotplug_handler = new UseQtEventDriver(_usb.ctx);
        _hotplug_thread = new QThread();
        _hotplug_handler->moveToThread(_hotplug_thread);
        _hotplug_thread->start();
        
        _hotplug->init(_usb.ctx);
     
        return 0;
    }
    
    catch(zmq::error_t& ex) {
        qDebug()<< "failed to init zmq:" << ex.what();
        return 1;
    }
}

void AppController::register_pub_port(int new_port) {
    _bon->registerService("_charger-service-pub._tcp", new_port);   
    qDebug() << "pub service now available on port:" << new_port;
}

void AppController::register_msg_port(int new_port) {
    _bon->registerService("_charger-service-msg._tcp", new_port);   
    qDebug() << "message handling service is now available on port:" << new_port;
}

void AppController::notify_hotplug_event(bool added, int vendor, int product, QString sn)  {
    qDebug() << "hotplug event for vendor:" << vendor << ", product:" << product << ", serial number:" << sn << ", registry:" << _registry;
    if(added)
        _registry->activate_device(vendor, product, sn);
    else
        _registry->deactivate_device(vendor, product);
}

void AppController::device_added(QString key) {
    qDebug() << "a device was added to the registry:" << key;
}

void AppController::device_removed(QString key) {
    qDebug() << "a device was removed from the registry:" << key;
}
