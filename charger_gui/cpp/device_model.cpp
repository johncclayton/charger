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
    
    startTimer(2000);
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    Q_FOREACH(QString k, _model.keys()) {
        _controller->messageBus()->getDeviceInformation(k);
    }
}

void debugChannel(ChannelStatus* c, int n) {
    qDebug() << n << "inputV:" << c->inputVoltage();
    qDebug() << n << "outputV:" << c->outputVoltage();
    qDebug() << n << "outputP:" << c->outputPower();
    qDebug() << n << "outputC:" << c->outputCurrent();
    
    qDebug() << n << "tempInt:" << c->tempInternal();
    qDebug() << n << "tempExt:" << c->tempExternal();

    qDebug() << n << "cell1:" << c->cell1()->voltage() << ", resistance:" << c->cell1()->resistance();
    qDebug() << n << "cell2:" << c->cell2()->voltage() << ", resistance:" << c->cell2()->resistance();
    qDebug() << n << "cell3:" << c->cell3()->voltage() << ", resistance:" << c->cell3()->resistance();
    qDebug() << n << "cell4:" << c->cell4()->voltage() << ", resistance:" << c->cell4()->resistance();
    qDebug() << n << "cell5:" << c->cell5()->voltage() << ", resistance:" << c->cell5()->resistance();
    qDebug() << n << "cell6:" << c->cell6()->voltage() << ", resistance:" << c->cell6()->resistance();
    qDebug() << n << "cell7:" << c->cell7()->voltage() << ", resistance:" << c->cell7()->resistance();
    qDebug() << n << "cell8:" << c->cell8()->voltage() << ", resistance:" << c->cell8()->resistance();
    qDebug() << n << "cell9:" << c->cell9()->voltage() << ", resistance:" << c->cell9()->resistance();
    qDebug() << n << "cell10:" << c->cell10()->voltage() << ", resistance:" << c->cell10()->resistance();
}

void DeviceModel::resetModels() {
    Q_FOREACH(QObject* info, _devices)
        info->deleteLater();
    _devices.clear();
    
    Q_FOREACH(QVariantMap m, _model.values()) {
        QVariantMap dev_info = m["info"].toMap(); 
        QList<QVariant> channels = m["channels"].toList();
        
        DeviceInfo* info = new DeviceInfo;
        info->setKey(m["key"].toString());
        info->setFromJson(variantMapToJson(dev_info));
        if(channels.length() == 2) {
            info->setChannel1FromJson(variantMapToJson(channels.at(0).toMap()));
            info->setChannel2FromJson(variantMapToJson(channels.at(1).toMap()));
        } else {
            qDebug() << "didnt find channels data to load into model";
        }
        
        if(info->product().contains("icharger", Qt::CaseInsensitive) && info->product().contains("4010"))
            info->setImageSource("qrc:/images/icharger_4010_duo.png");
        if(info->product().contains("icharger", Qt::CaseInsensitive) && info->product().contains("406"))
            info->setImageSource("qrc:/images/icharger_406_duo.png");
        if(info->product().contains("icharger", Qt::CaseInsensitive) && info->product().contains("308"))
            info->setImageSource("qrc:/images/icharger_308_duo.png");
        
        qDebug() << "key:" << info->key();
        debugChannel(info->channel1(), 1);
        debugChannel(info->channel2(), 2);
        
        _devices.append(info);
    }
        
    _ctx->setContextProperty("devices", QVariant::fromValue(_devices));
}

DeviceInfo* DeviceModel::getDeviceInfo(QString key) {
    if(key.length() == 0)
        return 0;
    
    Q_FOREACH(QObject* o, _devices) {
        DeviceInfo* info = dynamic_cast<DeviceInfo*>(o);
        if(info && info->key() == key) {
            return info;
        }
    }
    
    qDebug() << "get device info resulted in disaster for key:" << key;
    Q_ASSERT(false);
    
    return 0;
}

void DeviceModel::messageBusAlive(bool alive) {
    if(alive) {
        // fetch all the models...
        _controller->messageBus()->getDevices();
    } else {
        // clear the data model...
        Q_FOREACH(QString key, _model.keys()) {
            Q_EMIT deviceAddedRemoved(false, key);
            _ctx->setContextProperty(key, 0);
        }
        
        _model.clear();
        resetModels();
        
        Q_EMIT jsonDataChanged();
    }
}

void DeviceModel::processDeviceInfoUpdated(QString key, QVariantMap data) {
    qDebug() << "stored data for item:" << key;
    
    bool newItem = !_model.contains(key);
        
    _model[key] = data;
    
    resetModels();

    Q_EMIT jsonDataChanged();

    _ctx->setContextProperty(key, data);
    
    if(newItem)
        Q_EMIT deviceAddedRemoved(true, key);
    else
        Q_EMIT deviceInfoUpdated(key);
}

void DeviceModel::processDevicesUpdated(QVariantMap data) {
    if(data.contains("devices") && data.contains("count")) {
        QVariantList devices(data["devices"].toList());
        for(int index = 0; index < devices.size(); ++index) {
            const QVariantMap o = devices.at(index).toMap();
            _controller->messageBus()->getDeviceInformation(o["key"].toString());
        }    
    }
}

void DeviceModel::processDeviceAddedRemoved(bool added, QString key) {
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

