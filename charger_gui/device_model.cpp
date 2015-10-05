#include "device_model.h"

DeviceModel::DeviceModel(QSharedPointer<ClientMessagingController> c, QObject *parent) : 
    QJsonModel(parent),
    _controller(c) 
{
    connect(c.data(), SIGNAL(messageBusChanged()), this, SLOT(messageBusInstantiated()));    
}

DeviceModel::~DeviceModel() {
    
}

void DeviceModel::messageBusInstantiated() {
    // drop all existing signals/slots...    
    
    // drop model content...
    
    // make new ones!
    
}
