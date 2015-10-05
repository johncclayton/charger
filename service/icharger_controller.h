#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>

#include "zmq/publisher.h"
#include "usb/icharger_usb.h"

class iCharger_DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit iCharger_DeviceController(Publisher_ptr pub, icharger_usb_ptr p, QObject *parent = 0);
    virtual ~iCharger_DeviceController();
    
    icharger_usb_ptr device() { return _device; }
    
    void publish_device_json();
    void publish_channel_json(int index);
        
signals:
    
public slots:
    void handleTimeout();
    
private:
    QTimer* _timer;
    Publisher_ptr _pub;
    icharger_usb_ptr _device;
    
    QByteArray _latest_device_json;
    QByteArray _latest_channel_json[2];
};

typedef QSharedPointer<iCharger_DeviceController> iCharger_DeviceController_ptr;

#endif // DEVICE_CONTROLLER_H
