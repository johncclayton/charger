#ifndef USB_HOTPLUGLISTENER_H
#define USB_HOTPLUGLISTENER_H

#include <QObject>

class HotplugEventAdapter : public QObject
{
    Q_OBJECT
public:
    explicit HotplugEventAdapter(void* ctx, QObject *parent = 0);
    virtual ~HotplugEventAdapter();
    
    void process_hotplug_event(int event_type);
    
signals:
    void hotplug_event(bool device_arrived);
    
public slots:
    
private:
    struct Private;
    Private* _p;
};

#endif // USB_HOTPLUGLISTENER_H
