#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "usb/icharger_usb.h"
#include "usb/usb_hotpluglistener.h"
#include "usb/eventhandler.h"

#include "nzmqt/nzmqt.hpp"
#include "zmq/zmq_publisher.h"

#include "bonjour/bonjourserviceregister.h"

namespace nzmqt {
    class ZMQContext;
}

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    virtual ~Controller();
    
    int init();
signals:
    
public slots:
    void register_pub_port(int new_port);
    void notify_hotplug_event(bool added);
    
private:
    usb_context _usb;
    nzmqt::ZMQContext* _ctx;
    ZMQ_Publisher* _pub;
    
    BonjourServiceRegister* _bon;
    
    USB_HotPlugListener* _hotplug;
    EventHandler* _hotplug_handler;
    QThread* _hotplug_thread;
};

#endif // CONTROLLER_H
