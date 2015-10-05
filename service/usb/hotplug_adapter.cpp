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
    
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(dev, &desc);
    
    if(desc.idVendor != ICHARGER_VENDOR_ID)
        return 0;
    
    if(desc.idProduct == ICHARGER_PRODUCT_4010_DUO) {
        QString sn;
        
        if(event == LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED) {
            icharger_usb_ptr icharger_device(new icharger_usb(dev));
            sn = icharger_device->serialNumber();    
        }
        
        HotplugCallbackAdapter* obj = (HotplugCallbackAdapter*)(user_data);
        obj->process_hotplug_event(event, desc.idVendor, desc.idProduct, sn);
    }
    
    return 0;
}

struct HotplugCallbackAdapter::Private {
    libusb_hotplug_callback_handle handle;
    HotplugCallbackAdapter::Receiver* func;
    
    Private() : handle(0) {
        
    }
};

HotplugCallbackAdapter::HotplugCallbackAdapter(Receiver* func) : _p(new Private)
{
    _p->func = func;
}

void HotplugCallbackAdapter::init(libusb_context* ctx) {
    libusb_hotplug_callback_handle h;
    
    Q_ASSERT(_p);
    Q_ASSERT(_p->handle == 0);
    Q_ASSERT(ctx != 0);
    
    int rc = libusb_hotplug_register_callback(ctx,
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

HotplugCallbackAdapter::~HotplugCallbackAdapter() {
    if(_p->handle) {
        libusb_hotplug_deregister_callback(NULL, _p->handle);
        qDebug() << "deregistered hotplug callback";
    }
    
    delete _p;
    _p = 0;
}

void HotplugCallbackAdapter::process_hotplug_event(int event_type, int vendor, int product, QString sn) {
    Q_ASSERT(_p);    
    Q_ASSERT(_p->func);
    
    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event_type) {
        _p->func->callback(true, vendor, product, sn);        
    } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event_type) {
        _p->func->callback(false, vendor, product, sn);
    }
}
