#ifndef USB_HOTPLUGLISTENER_H
#define USB_HOTPLUGLISTENER_H

#include <QObject>
struct libusb_device;

class HotplugEventAdapter : public QObject
{
    Q_OBJECT
public:
    explicit HotplugEventAdapter(QObject *parent = 0);
    virtual ~HotplugEventAdapter();

    void init(void *ctx);    
    void process_hotplug_event(int event_type, libusb_device* dev, int vendor, int product, int sn_descriptor);
    
signals:
    void hotplug_event(bool device_arrived, libusb_device* dev, int vendor, int product, int sn_descriptor);
    
public slots:
    
private:
    struct Private;
    Private* _p;
};

#endif // USB_HOTPLUGLISTENER_H
