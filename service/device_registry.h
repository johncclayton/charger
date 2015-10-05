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
    
    QString deviceKey(int vendor, int product, QString sn);
    
    void activateDevice(int vendor, int product, QString sn);
    void deactivateDevice(int vendor, int product);
    DeviceMap devices() const { return _devices; }

signals:
    void deviceActivated(QString key);
    void deviceDeactivated(QString key);
    
public slots:
    void publishChargerState();
    
private:
    libusb_context* _ctx;
    Publisher_ptr _pub;
    DeviceMap _devices;
};

#endif

