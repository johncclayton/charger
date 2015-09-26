#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include "zmq/publisher.h"
#include "usb/icharger_usb.h"

class iCharger_DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit iCharger_DeviceController(Publisher_ptr pub, icharger_usb_ptr p, QObject *parent = 0);
    
    icharger_usb_ptr device() { return _device; }
    
signals:
    
public slots:
    
protected:
    void timerEvent(QTimerEvent *event);
    
private:
    Publisher_ptr _pub;
    icharger_usb_ptr _device;
};

typedef QSharedPointer<iCharger_DeviceController> iCharger_DeviceController_ptr;

#endif // DEVICE_CONTROLLER_H
