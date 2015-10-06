#include "device_model.h"
#include "message_bus.h"
#include "json_helper.h"

#define KeyRole Qt::UserRole + 100

DeviceModel::DeviceModel(QSharedPointer<ClientMessagingController> c, QQmlContext* ctx, QObject *parent) : 
    QObject(parent),
    _controller(c),
    _ctx(ctx)
{
    MessageBus* bus = c->messageBus();
    
    connect(bus, SIGNAL(deviceAddedRemoved(bool,QString)), this, SLOT(deviceAddedRemoved(bool,QString)));    
    connect(bus, SIGNAL(aliveChanged(bool)), this, SLOT(messageBusAlive(bool)));
    connect(bus, SIGNAL(getDeviceResponse(QString,QVariantMap)), this, SLOT(deviceInfoUpdated(QString,QVariantMap)));
    connect(bus, SIGNAL(getDevicesResponse(QVariantMap)), this, SLOT(devicesUpdated(QVariantMap)));
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::messageBusAlive(bool alive) {
    if(alive) {
        // fetch all the models...
        _controller->messageBus()->getDevices();
    } else {
        // clear the data model...
        _model.clear();
        replaceModel();
    }
}

void DeviceModel::deviceInfoUpdated(QString key, QVariantMap data) {
    qDebug() << "received info for key" << key << "device info:" << variantMapToJson(data);
}

void DeviceModel::devicesUpdated(QVariantMap data) {
    qDebug() << "devices have been updated" << data;
    if(data.contains("devices") && data.contains("count")) {
        QVariantList devices(data["devices"].toList());
        for(int index = 0; index < devices.size(); ++index) {
            const QVariantMap o = devices.at(index).toMap();
            _controller->messageBus()->getDeviceInformation(o["key"].toString());
        }    
    }
}

void DeviceModel::deviceAddedRemoved(bool added, QString key) {
    if(added) {
        _controller->messageBus()->getDeviceInformation(key);
    } else {
        // find this and remove it from the model       
    }
}

void DeviceModel::replaceModel() {
//    _ctx->setContextProperty("dataModel", _model);
}
