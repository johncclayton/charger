#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "device_model.h"
#include "device_info.h"
#include "message_bus.h"
#include "json_helper.h"

#define KeyRole Qt::UserRole + 100

DeviceModel::DeviceModel(QSharedPointer<ClientMessagingController> c, QQmlContext* ctx,  QObject *parent) : 
    QObject(parent),
    _controller(c),
    _ctx(ctx)
{
    MessageBus* bus = c->messageBus();
    
    connect(bus, SIGNAL(deviceAddedRemoved(bool,QString)), this, SLOT(deviceAddedRemoved(bool,QString)));    
    connect(bus, SIGNAL(aliveChanged(bool)), this, SLOT(messageBusAlive(bool)));
    connect(bus, SIGNAL(getDeviceResponse(QString,QVariantMap)), this, SLOT(deviceInfoUpdated(QString,QVariantMap)));
    connect(bus, SIGNAL(getDevicesResponse(QVariantMap)), this, SLOT(devicesUpdated(QVariantMap)));
    
    connect(this, SIGNAL(jsonDataChanged()), this, SLOT(resetModels()));
    
    resetModels();
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::resetModels() {
    QObjectList devices;
    
    Q_FOREACH(QVariantMap m, _model.values()) {
        QVariantMap dev_info = m;
        qDebug() << "using:" << dev_info;
        DeviceInfo* info = new DeviceInfo;
        info->setFromJson(variantMapToJson(dev_info));
        devices.append(info);
    }
    
    _ctx->setContextProperty("devices", QVariant::fromValue(devices));
}

void DeviceModel::messageBusAlive(bool alive) {
    if(alive) {
        // fetch all the models...
        _controller->messageBus()->getDevices();
    } else {
        // clear the data model...
        _model.clear();
        Q_EMIT jsonDataChanged();
    }
}

void DeviceModel::deviceInfoUpdated(QString key, QVariantMap data) {
    qDebug() << "retrieved data for item:" << key << "and stored it";
    _model[key] = data;
    Q_EMIT jsonDataChanged();
}

void DeviceModel::devicesUpdated(QVariantMap data) {
    if(data.contains("devices") && data.contains("count")) {
        QVariantList devices(data["devices"].toList());
        qDebug() << "got" << devices.size() << "devices for which I will get more details for";
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
        _model.remove(key);
        Q_EMIT jsonDataChanged();
    }
}

