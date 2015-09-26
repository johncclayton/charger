#ifndef USB_HOTPLUGLISTENER_H
#define USB_HOTPLUGLISTENER_H

#include <QObject>

class HotplugEventAdapter : public QObject
{
    Q_OBJECT
public:
    explicit HotplugEventAdapter(QObject *parent = 0);
    virtual ~HotplugEventAdapter();

    void init(void *ctx);    
    void process_hotplug_event(int event_type, int vendor, int product, QString sn);
    
signals:
    void hotplug_event(bool device_arrived, int vendor, int product, QString sn);
    
public slots:
    
private:
    struct Private;
    Private* _p;
};

#endif // USB_HOTPLUGLISTENER_H
