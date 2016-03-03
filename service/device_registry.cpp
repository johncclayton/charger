#include <QDebug>
#include "device_registry.h"

DeviceRegistry::DeviceRegistry(libusb_context* ctx, Publisher_ptr pub, QObject *owner) : QObject(owner), _ctx(ctx), _pub(pub) {
}

DeviceRegistry::~DeviceRegistry() {
    _ctx = 0;
}

QString DeviceRegistry::deviceKey(int vendor, int product, QString sn) {
    return QString("%1-%2-%3").arg(vendor, 1, 16).arg(product, 1, 16).arg(sn).toUpper();
}

void DeviceRegistry::activateDevice(int vendor, int product, QString sn) {
    Q_ASSERT(_ctx != 0);
    Q_ASSERT(vendor != 0);
    Q_ASSERT(product != 0);
    
    // TODO: instantiate the right code - generic instead of iCharger specific.
    charger_list match = icharger_usb::all_chargers(_ctx, vendor, product, sn);
    for(int index = 0; index < match.size(); ++index) {
        QString key(deviceKey(vendor, product, sn));
        icharger_usb_ptr obj(match[index]);
        iCharger_DeviceController_ptr device_ptr(new iCharger_DeviceController(key, obj));
        int r = device_ptr->device()->acquire();
        if(0 == r) {
            qDebug() << "device registered:" << key;
            _devices.insert(key, device_ptr);
            Q_EMIT deviceActivated(key);
        } else {
            qDebug() << "wasn't able to claim the device - result code:" << r;
        }
    }
}

void DeviceRegistry::deactivateDevice(int vendor, int product) {
    Q_ASSERT(vendor != 0);
    Q_ASSERT(product != 0);

    for(DeviceMap::iterator it = _devices.begin(); it != _devices.end(); /* nothing - see below */) {
        icharger_usb_ptr ptr = it.value()->device();
        Q_ASSERT(ptr);
        Q_ASSERT(ptr.data());
            
        if(ptr->vendorId() == vendor && ptr->productId() == product) {
            // test if the device is open - do this by asking for its serial number - if this fails, it
            // must be the one that died?
            QString sn = ptr->serialNumber();
            
            if(sn.isNull() || sn.isEmpty()) {
                qDebug() << "removing" << it.key() << "from list of registered devices";
                
                Q_EMIT deviceDeactivated(it.key());
                it = _devices.erase(it);
                
                /* do not increment it */
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }    
}
