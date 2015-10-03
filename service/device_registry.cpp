#include <QDebug>
#include "device_registry.h"

DeviceRegistry::DeviceRegistry(libusb_context* ctx, Publisher_ptr pub, QObject *owner) : QObject(owner), _ctx(ctx), _pub(pub) {
}

DeviceRegistry::~DeviceRegistry() {
    _ctx = 0;
}

QString DeviceRegistry::device_key(int vendor, int product, QString sn) {
    return QString("%1-%2-%3").arg(vendor, 1, 16).arg(product, 1, 16).arg(sn).toUpper();
}

void DeviceRegistry::activate_device(int vendor, int product, QString sn) {
    Q_ASSERT(_ctx != 0);
    Q_ASSERT(vendor != 0);
    Q_ASSERT(product != 0);
    
    charger_list match = icharger_usb::all_chargers(_ctx, vendor, product, sn);
    if(match.size()) {
        iCharger_DeviceController_ptr device_ptr(new iCharger_DeviceController(_pub, match[0]));
        if(0 == device_ptr->device()->acquire()) {
            QString key(device_key(vendor, product, sn));
            _devices.insert(key, device_ptr);
            Q_EMIT device_activated(key);
        } else {
            qDebug() << "wasn't able to claim the device - ignoring it";
        }
    }
}

void DeviceRegistry::deactivate_device(int vendor, int product) {
    Q_ASSERT(vendor != 0);
    Q_ASSERT(product != 0);

    for(DeviceMap::iterator it = _devices.begin(); it != _devices.end(); ++it) {
        icharger_usb_ptr ptr = it.value()->device();
        if(ptr->vendorId() == vendor && ptr->productId() == product) {
            // test if the device is open - do this by asking for its serial number - if this fails, it
            // must be the one that died?
            QString sn = ptr->serial_number();
            if(sn.isNull() || sn.isEmpty()) {
                qDebug() << "removing" << it.key() << "from list of registered devices";
                Q_EMIT device_deactivated(it.key());
                _devices.remove(it.key());
                return;
            }
        }
    }    
}
