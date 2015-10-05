#include "device_model.h"
#include "message_bus.h"

DeviceModel::DeviceModel(QSharedPointer<ClientMessagingController> c, QObject *parent) : 
    QObject(parent),
    _controller(c),
    _model(new QJsonModel)
{
    MessageBus* bus = c->messageBus();
    connect(bus, SIGNAL(deviceAddedRemoved(bool,QString)), this, SLOT(deviceAddedRemoved(bool,QString)));    
    connect(bus, SIGNAL(aliveChanged(bool)), this, SLOT(messageBusAlive(bool)));
    connect(bus, SIGNAL(getDeviceResponse(QString,QVariantMap)), this, SLOT(deviceInfoUpdated(QString,QVariantMap)));
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::messageBusAlive(bool alive) {
    if(alive) {
        // fetch all the models...
        _controller->messageBus()->getDevices();
    } else {
        // clear the data model...
        _model->loadJson(QJsonDocument());
    }
}

void DeviceModel::deviceInfoUpdated(QString key, QVariantMap data) {
    qDebug() << "received info for key" << key << "device info:" << data;
}

void DeviceModel::deviceAddedRemoved(bool added, QString key) {
    if(added) {
        _controller->messageBus()->getDeviceInformation(key);
    } else {
        // find this and remove it from the model.
    }
}

