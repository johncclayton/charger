#include <QDebug>

#include "usb/hotplug_adapter.h"
#include "usb/icharger_usb.h"
#include "libusb.h"

int hotplug_callback(struct libusb_context *ctx, 
                     struct libusb_device *dev,
                     libusb_hotplug_event event, 
                     void *user_data) 
{
    Q_UNUSED(ctx);
    Q_UNUSED(dev);
    
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(dev, &desc);
        
    if(desc.idVendor != ICHARGER_VENDOR_ID)
        return 0;
    
    if(desc.idProduct == ICHARGER_PRODUCT_4010_DUO) {
        icharger_usb_ptr icharger_device(new icharger_usb(dev));
        if(!icharger_device->acquire()) {
            qCritical() << "unable to open the device in order to get its serial number";
            return 0;
        }
    
        QString sn = icharger_device->serial_number();    
    
        HotplugEventAdapter* obj = (HotplugEventAdapter*)(user_data);
        obj->process_hotplug_event(event, desc.idVendor, desc.idProduct, sn);
    }
    
    return 0 /* this means we're expecting more events - don't remove the callback please */;
}

struct HotplugEventAdapter::Private {
    libusb_hotplug_callback_handle handle;
    
    Private() : handle(0) {
        
    }
};

HotplugEventAdapter::HotplugEventAdapter(QObject *parent) : QObject(parent), _p(new Private)
{
}

void HotplugEventAdapter::init(void *ctx) {
    libusb_hotplug_callback_handle h;
    
    int rc = libusb_hotplug_register_callback((libusb_context *)ctx,
                                              (libusb_hotplug_event)(LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED + LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT), 
                                              LIBUSB_HOTPLUG_ENUMERATE, 
                                              LIBUSB_HOTPLUG_MATCH_ANY, 
                                              LIBUSB_HOTPLUG_MATCH_ANY,
                                              LIBUSB_HOTPLUG_MATCH_ANY, 
                                              hotplug_callback, 
                                              this,
                                              &h);
    if(rc == 0)
        _p->handle = h;
}

HotplugEventAdapter::~HotplugEventAdapter() {
    if(_p->handle)
        libusb_hotplug_deregister_callback(NULL, _p->handle);
    delete _p;
}

void HotplugEventAdapter::process_hotplug_event(int event_type, int vendor, int product, QString sn) {
    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event_type) {
        hotplug_event(true, vendor, product, sn);        
    } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event_type) {
        hotplug_event(false, vendor, product, sn);
    }
}
