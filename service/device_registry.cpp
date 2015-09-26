
#include "device_registry.h"

DeviceRegistry::DeviceRegistry(QObject *owner) : QObject(owner) {
    
}

DeviceRegistry::~DeviceRegistry() {
    
}

void DeviceRegistry::activate_device(libusb_device* dev, int vendor, int product, QString sn) {
    Q_UNUSED(dev);
    Q_UNUSED(vendor);
    Q_UNUSED(product);
    Q_UNUSED(sn);
    
}

void DeviceRegistry::deactivate_device(libusb_device* dev, int vendor, int product, QString sn) {
    Q_UNUSED(dev);
    Q_UNUSED(vendor);
    Q_UNUSED(product);
    Q_UNUSED(sn);
    
}
