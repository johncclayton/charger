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
        
        while(true) {    
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 750000;
            
            libusb_handle_events_timeout(context, &tv);
        }    
    }
    catch(...) {
        qDebug() << "callback adapter threw an exception - its aborting";
    }
}

void LibUsbEventAdapter::callback(bool activation, int vendorId, int productId, QString sn) {
    Q_EMIT hotplug_event(activation, vendorId, productId, sn);
}




