#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "icharger/icharger_message_keys.h"
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
    
    connect(bus, SIGNAL(aliveChanged(bool)), this, SLOT(messageBusAlive(bool)));
    connect(bus, SIGNAL(deviceAddedRemoved(bool,QString)), this, SLOT(processDeviceAddedRemoved(bool,QString)));    
    connect(bus, SIGNAL(getDeviceResponse(QString,QVariantMap)), this, SLOT(processDeviceInfoUpdated(QString,QVariantMap)));
    connect(bus, SIGNAL(getDevicesResponse(QVariantMap)), this, SLOT(processDevicesUpdated(QVariantMap)));
        
    ctx->setContextProperty("devicesModel", this);
    
    resetModels();
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::resetModels() {
    QObjectList devices;
    
    Q_FOREACH(QVariantMap m, _model.values()) {
        QVariantMap dev_info = m["info"].toMap(); 
        DeviceInfo* info = new DeviceInfo;
        info->setFromJson(variantMapToJson(dev_info));
        if(info->product().contains("icharger", Qt::CaseInsensitive) && info->product().contains("4010"))
            info->setImageSource("qrc:/images/icharger_4010_duo.png");
        if(info->product().contains("icharger", Qt::CaseInsensitive) && info->product().contains("406"))
            info->setImageSource("qrc:/images/icharger_406_duo.png");
        if(info->product().contains("icharger", Qt::CaseInsensitive) && info->product().contains("308"))
            info->setImageSource("qrc:/images/icharger_308_duo.png");
        devices.append(info);
    }
    
    // current list of devices available...
    _ctx->setContextProperty("devices", QVariant::fromValue(devices));
}

void DeviceModel::messageBusAlive(bool alive) {
    if(alive) {
        // fetch all the models...
        _controller->messageBus()->getDevices();
    } else {
        // clear the data model...
        Q_FOREACH(QString key, _model.keys())
            Q_EMIT deviceAddedRemoved(false, key);
        _model.clear();
        resetModels();
        Q_EMIT jsonDataChanged();
    }
}

void DeviceModel::processDeviceInfoUpdated(QString key, QVariantMap data) {
    qDebug() << "retrieved data for item:" << key << "and stored it";
    _model[key] = data;
    
    resetModels();

    Q_EMIT jsonDataChanged();
    Q_EMIT deviceAddedRemoved(true, key);
}

void DeviceModel::processDevicesUpdated(QVariantMap data) {
    if(data.contains("devices") && data.contains("count")) {
        QVariantList devices(data["devices"].toList());
        qDebug() << "fetching more details for" << devices.size() << "device(s)";
        for(int index = 0; index < devices.size(); ++index) {
            const QVariantMap o = devices.at(index).toMap();
            _controller->messageBus()->getDeviceInformation(o["key"].toString());
        }    
    }
}

void DeviceModel::processDeviceAddedRemoved(bool added, QString key) {
    qDebug() << "booooooom?" << added << "," << key;
    if(added) {
        _controller->messageBus()->getDeviceInformation(key);
    } else {
        qDebug() << "the device with this key is being removed:" << key;
        // find this and remove it from the model       
        _model.remove(key);
        resetModels();
        Q_EMIT jsonDataChanged();
        Q_EMIT deviceAddedRemoved(false, key);
    }
}

