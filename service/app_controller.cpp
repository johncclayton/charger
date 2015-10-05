#include "app_controller.h"

#include <QtGlobal>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QScopedPointer>
#include <QDebug>

#include "usb/icharger_usb.h"
#include "usb/eventhandler.h"
#include "message_handler.h"
#include "json_helper.h"

#include "nzmqt/nzmqt.hpp"
#include "zmq/publisher.h"

#include "bonjourserviceregister.h"

using namespace nzmqt;
using namespace std;

AppController::AppController(QObject *parent) : QObject(parent), 
    _ctx(0),
    _pub(0), 
    _hotplug_handler(0),
    _registry(0),
    _msg_handler(0)
{
    startTimer(1000);
}

AppController::~AppController() {    
    qDebug() << "app controller being destroyed";
    _hotplug_handler->quit();
    _hotplug_handler->deleteLater();    
    _ctx->stop();
}

int AppController::init(int pub_port, int msg_port) {
    try {
        // ZeroMQ to send / receive messages - requires a context.
        _ctx = createDefaultContext(this);
        _ctx->start();
        
        // Get the message infrastructure ready (pub/sub and messaging).
        _pub = Publisher_ptr(new Publisher(_ctx, this));
        
        // Bonjour system needs to publish our ZMQ publisher port
        _bonjour_msg = new BonjourServiceRegister(this);
        _bonjour_pub = new BonjourServiceRegister(this);

        _registry = new DeviceRegistry(_usb.ctx, _pub, this);
        
        connect(_registry, SIGNAL(deviceActivated(QString)),
                         this, SLOT(deviceAdded(QString)));
        connect(_registry, SIGNAL(deviceDeactivated(QString)),
                         this, SLOT(deviceRemoved(QString)));
               
        // Respond to changes to the publisher port
        connect(_pub.data(), SIGNAL(portChanged(int)), 
                this, SLOT(registerPublisherPort(int)));
                
        // bind the publisher to cause it to find a local ephemeral port and publish it
        if(!_pub->bind(pub_port)) {
            qDebug() << "unable to bind the zmq publisher to its interface";
            return 1;
        }
        
        _msg_handler = new MessageHandler(_ctx);
        connect(_msg_handler, SIGNAL(portChanged(int)), this, SLOT(registerMessagePort(int)));
        connect(_msg_handler, SIGNAL(requesetReceived(QList<QByteArray>,QList<QByteArray>)), 
                this, SLOT(processMessageRequest(QList<QByteArray>,QList<QByteArray>)));
        
        if(!_msg_handler->bind(msg_port)) {
            qDebug() << "unable to bind the zmq message handler to its interface";
            return 2;
        }
        
        // Kick off a listener for USB hotplug events - so we keep our device list fresh,
        // this is a thread and it runs its own event loop internally.  
        _hotplug_handler = new LibUsbEventAdapter(_usb.ctx);
        connect(_hotplug_handler, SIGNAL(hotplugEvent(bool,int,int,QString)), 
                this, SLOT(notifyHotplugEvent(bool,int,int,QString)), Qt::QueuedConnection);
        _hotplug_handler->start();
               
        return 0;
    }
    
    catch(zmq::error_t& ex) {
        qDebug()<< "failed to init zmq:" << ex.what();
        return 1;
    }
}

void AppController::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    _pub->publishHeartbeat();
}

void AppController::registerPublisherPort(int new_port) {
    Q_ASSERT(_bonjour_pub);
    _bonjour_pub->registerService("_charger-service-pub._tcp", new_port);   
    qDebug() << "publisher service now available on port:" << new_port;
}

void AppController::registerMessagePort(int new_port) {
    Q_ASSERT(_bonjour_msg);
    _bonjour_msg->registerService("_charger-service-msg._tcp", new_port);   
    qDebug() << "messaging service now available on port:" << new_port;
}

void AppController::notifyHotplugEvent(bool added, int vendor, int product, QString sn)  {
    Q_ASSERT(_registry);

    qDebug() << "hotplug event for vendor:" << vendor << ", product:" << product << ", serial number:" << sn;
    if(added)
        _registry->activateDevice(vendor, product, sn);
    else
        _registry->deactivateDevice(vendor, product);
}

void AppController::deviceAdded(QString key) {
    _pub->publishDeviceAddedRemoved(true, key);
}

void AppController::deviceRemoved(QString key) {
    _pub->publishDeviceAddedRemoved(false, key);
}

void AppController::processMessageRequest(QList<QByteArray> return_path, QList<QByteArray> payload) {
    QVariantMap response;

    // depends on what is being asked - our API is pretty simple now... 
    QString request = QString::fromUtf8(payload.at(0));
    if(request == "get-devices") {
        response = doGetDevices();
    } else if(request == "get-device") {
        QString key = payload.at(1);
        response = doGetDevice(key);
    }
    
    MessageHandler* msg_handler = dynamic_cast<MessageHandler*>(sender());
    if(!response.isEmpty() && msg_handler) {
        QList<QByteArray> data;
        data.append(variantMapToJson(response));
        msg_handler->sendResponse(return_path, data);
    }
    
}

QVariantMap AppController::doGetDevices() {
    DeviceMap all_devices = _registry->devices();
    QVariantMap response;
    
    response["action"] = "get-devices";
    response["count"] = all_devices.count();
    
    QVariantList device_list;
    for(DeviceMap::const_iterator it = all_devices.begin(); it != all_devices.end(); ++it) {
        QVariantMap device;
        device["key"] = it.key();
        device["protected"] = false;
        device["vendorId"] = it.value()->device()->vendorId();
        device["productId"] = it.value()->device()->productId();
        device["manufacturer"] = it.value()->device()->manufacturer();
        device_list.append(device);
    }
    
    response["devices"] = device_list;
    
    return response;
}

QVariantMap AppController::doGetDevice(QString key) {
    if(!_registry->devices().contains(key))
        return QVariantMap();
    iCharger_DeviceController_ptr device(_registry->devices().find(key).value());
    QVariantMap response;
    response["action"] = "get-device";
    response["device"] = jsonToVariantMap(device->toJson());
    return response;
}
