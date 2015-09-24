#ifndef USB_HOTPLUGLISTENER_H
#define USB_HOTPLUGLISTENER_H

#include <QObject>

class USB_HotPlugListener : public QObject
{
    Q_OBJECT
public:
    explicit USB_HotPlugListener(void* ctx, QObject *parent = 0);
    virtual ~USB_HotPlugListener();
    
    void process_hotplug_event(int event_type);
    
signals:
    void hotplug_event(bool device_arrived);
    
public slots:
    
private:
    struct Private;
    Private* _p;
};

#endif // USB_HOTPLUGLISTENER_H
