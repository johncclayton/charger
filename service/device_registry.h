#ifndef __DEV_REG_H
#define __DEV_REG_H

#include <QObject>
#include <QMap>
#include <QPair>

#include "zmq/publisher.h"
#include "icharger_controller.h"

typedef QMap<QString, iCharger_DeviceController_ptr> DeviceMap;

/**
 * Responsible for instantiating and keeping track of all currently
 * connected devices in the system.
 */
class DeviceRegistry : public QObject {
Q_OBJECT
public:
    DeviceRegistry(libusb_context* ctx, Publisher_ptr pub, QObject* owner = 0);
    virtual ~DeviceRegistry();
    
    QString device_key(int vendor, int product, QString sn);
    
    void activate_device(int vendor, int product, QString sn);
    void deactivate_device(int vendor, int product);

signals:
    void device_activated(QString key);
    void device_deactivated(QString key);
    
private:
    libusb_context* _ctx;
    Publisher_ptr _pub;
    DeviceMap _devices;
};

#endif

