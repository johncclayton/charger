#include <QDebug>
#include <QThread>
#include <QSharedPointer>

#include <functional>
#include <algorithm>

#include "libusb.h"
#include "eventhandler.h"

LibUsbEventAdapter::LibUsbEventAdapter(libusb_context *context, QObject *parent) :
    QThread(parent), context(context)
{
}

LibUsbEventAdapter::~LibUsbEventAdapter() {
    qDebug() << "usb hotplug event adapter destroyed";
}

void LibUsbEventAdapter::run() {
    QSharedPointer<HotplugCallbackAdapter> adapter(new HotplugCallbackAdapter(this));

    try {
        adapter->init(context);
        
        int completed = 0;
        
        retry:
        
        if(libusb_try_lock_events(context) == 0) {
            completed = 0;
            while(!completed) {
                if(!libusb_event_handling_ok(context)) {
                    libusb_unlock_events(context);
                    goto retry;
                }
                    
                struct timeval tv;
                tv.tv_sec = 0;
                tv.tv_usec = 750000;
                
                libusb_handle_events_timeout_completed(context, &tv, &completed);
                
                libusb_unlock_events(context);
            }
        } else {
            // another thread is event handling...
            libusb_lock_event_waiters(context);
            
            completed = 0;
            while(!completed) {
                if(!libusb_event_handler_active(context)) {
                    libusb_unlock_event_waiters(context);
                    goto retry;
                }
                
                libusb_wait_for_event(context, NULL);
            }
            
            libusb_unlock_event_waiters(context);
        }
    }
    catch(...) {
        qDebug() << "callback adapter threw an exception - its aborting";
    }
}

void LibUsbEventAdapter::callback(bool activation, int vendorId, int productId, QString sn) {
    Q_EMIT hotplugEvent(activation, vendorId, productId, sn);
}




