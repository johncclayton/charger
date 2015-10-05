#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVariantMap>

#include "usb/icharger_usb.h"
#include "usb/eventhandler.h"

#include "nzmqt/nzmqt.hpp"
#include "zmq/publisher.h"

#include "device_registry.h"
#include "message_handler.h"

class BonjourServiceRegister;

/**
 * @brief The AppController class is responsible for bringing all the back end server components
 * online and hooking them into a cohensive whole.  It's the puppet master - there is one of these
 * instantiated from main and its job is to run the circus.  With bells on.
 * 
 * The AppController will ensure that the publisher and messaging end points are allocated
 * the right ports, usually ephemeral but they can be fixed by command line parameters.  The port
 * numbers are then publishing using Bonjour.
 * 
 * The AppController will also run a USB hotplug controller in another thread - so that we can 
 * respond to plug events and attempt to instantiate the right USB code to take care of the
 * device that has been found (only if we know what the heck it is of course).
 * 
 * Devices that are recognized are give to the DeviceRegistry - its responsible for keeping tracking
 * of a unique ID per connected device, and for holding onto a pointer to both the libusb_device 
 * object and a piece of code that drives it - e.g. for iCharger 4010 DUO you'd expect to see a single
 * libusb_device* object as well as an instance of iCharger_DeviceController.
 * 
 * Devices that are removed will be instanty removed from the DeviceRegistry.
 */
class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = 0);
    virtual ~AppController();
    
signals:
    
public slots:
    int init(int pub_port = 0, int msg_port = 0);

    void registerPublisherPort(int new_port);
    void registerMessagePort(int new_port);
    
    void notifyHotplugEvent(bool added, int vendor, int product, QString sn);
    void deviceAdded(QString key);
    void deviceRemoved(QString key);
    
protected:
    void timerEvent(QTimerEvent *event);
    
protected slots:
    void processMessageRequest(QList<QByteArray> return_path, QList<QByteArray> payload);    
    QVariantMap doGetDevices();
    QVariantMap doGetDevice(QString key);
    
private:
    usb_context _usb;
    nzmqt::ZMQContext* _ctx;
    Publisher_ptr _pub;
    
    // ensures we publish services via bonjour/zeroconf
    BonjourServiceRegister* _bonjour_pub;
    BonjourServiceRegister* _bonjour_msg;
    
    // handles usb hotplug events - see also notify_hotplug_event
    LibUsbEventAdapter* _hotplug_handler;
    
    // the internal device model - its really just a collection of stuff that can 
    // then be sent over the wire to listeners.  Events update this model and we
    // then push parts or all of it over the wire via ZMQ in JSON
    DeviceRegistry* _registry;
    
    // the message handler talks with GUI processes 
    MessageHandler* _msg_handler;
};

#endif // CONTROLLER_H
