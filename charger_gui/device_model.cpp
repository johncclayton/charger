#include "device_model.h"
#include "message_bus.h"

DeviceModel::DeviceModel(QSharedPointer<ClientMessagingController> c, QObject *parent) : 
    QObject(parent),
    _controller(c),
    _model(new QJsonModel)
{
    MessageBus* bus = c->messageBus();
    connect(bus, SIGNAL(deviceAddedRemoved(bool,QString)), this, SLOT(deviceAddedRemoved(bool,QString)));    
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::deviceAddedRemoved(bool added, QString key) {
    if(added) {
        // go fetch all the details for the device. 
        
    } else {
        // find it in the model and remove it.
        
    }
}

