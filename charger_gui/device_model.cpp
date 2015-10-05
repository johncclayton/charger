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
    
}

void DeviceModel::deviceAddedRemoved(bool added, QString key) {
    
}

