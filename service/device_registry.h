#ifndef __DEV_REG_H
#define __DEV_REG_H

#include <QObject>
struct libusb_device;

/**
 * Responsible for instantiating and keeping track of all currently
 * connected devices in the system.  
 */
class DeviceRegistry : public QObject {
Q_OBJECT
public:
    DeviceRegistry(QObject* owner = 0);
    virtual ~DeviceRegistry();
      
    void activate_device(libusb_device* dev, int vendor, int product, QString sn);
    void deactivate_device(libusb_device* dev, int vendor, int product, QString sn);

private:
    
};

#endif

