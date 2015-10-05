#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>

#include "usb/icharger_usb.h"

class iCharger_DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit iCharger_DeviceController(QString key, icharger_usb_ptr p, QObject *parent = 0);
    virtual ~iCharger_DeviceController();
    
    icharger_usb_ptr device() { return _device; }
    QString key() const { return _key; }
    QByteArray toJson() const;
    
signals:
    void onChargerStateChanged();
    
public slots:
    void handleTimeout();
    
private:
    QTimer* _timer;
    
    QString _key;
    icharger_usb_ptr _device;
    
    QByteArray _latest_device_json;
    QByteArray _latest_channel_json[2];
};

typedef QSharedPointer<iCharger_DeviceController> iCharger_DeviceController_ptr;

#endif // DEVICE_CONTROLLER_H
