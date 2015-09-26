
#include "device_registry.h"

DeviceRegistry::DeviceRegistry(QObject *owner) : QObject(owner) {
    
}

DeviceRegistry::~DeviceRegistry() {
    
}

void DeviceRegistry::activate_device(int vendor, int product, QString sn) {
    Q_UNUSED(vendor);
    Q_UNUSED(product);
    Q_UNUSED(sn);
    
}

void DeviceRegistry::deactivate_device(int vendor, int product, QString sn) {
    Q_UNUSED(vendor);
    Q_UNUSED(product);
    Q_UNUSED(sn);
}
