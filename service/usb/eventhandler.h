#ifndef USB_EVENTHANDLER_H
#define USB_EVENTHANDLER_H

#include <QThread>

#include "hotplug_adapter.h"

struct libusb_context;

class LibUsbEventAdapter : public QThread, private HotplugCallbackAdapter::Receiver
{
    Q_OBJECT

public:
    LibUsbEventAdapter(libusb_context *context, QObject *parent = 0);
    ~LibUsbEventAdapter();
    
    void run();

signals:
    void hotplugEvent(bool activated, int vendor, int product, QString sn);

private:
    void callback(bool activation, int vendorId, int productId, QString sn);
    
    libusb_context *context;
};

#endif // USB_EVENTHANDLER_H
