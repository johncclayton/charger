#include "device_registry.h"

DeviceRegistry::DeviceRegistry(libusb_context* ctx, QObject *owner) : QObject(owner), _ctx(ctx) {
    
}

DeviceRegistry::~DeviceRegistry() {
    _ctx = 0;
}

QString DeviceRegistry::device_key(int vendor, int product, QString sn) {
    return QString("%1-%2-%s").arg(vendor).arg(product).arg(sn);
}

void DeviceRegistry::activate_device(int vendor, int product, QString sn) {
    Q_ASSERT(_ctx != 0);
    Q_ASSERT(vendor != 0);
    Q_ASSERT(product != 0);
    Q_ASSERT(!sn.isEmpty());
    
    charger_list match = icharger_usb::all_chargers(_ctx, vendor, product, sn);
    if(match.size()) {
        icharger_usb_ptr ptr = match[0];    
        QString key(device_key(vendor, product, sn));
        _devices[key] = ptr;
        Q_EMIT device_activated(key);
    }
}

void DeviceRegistry::deactivate_device(int vendor, int product) {
    for(DeviceMap::iterator it = _devices.begin(); it != _devices.end(); ++it) {
        icharger_usb_ptr ptr = it.value();
        if(ptr->vendorId() == vendor && ptr->productId() == product) {
            // test if the device is open - do this by asking for its serial number - if this fails, it
            // must be the one that died?
            QString sn = ptr->serial_number();
            if(sn.isEmpty()) {
                _devices.remove(it.key());
                Q_EMIT device_deactivated(it.key());
                return;
            }
        }
    }    
}
