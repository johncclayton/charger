#include <QDebug>

#include "usb/hotplug_adapter.h"
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

    qDebug() << "got a hotplug event";
    
    HotplugEventAdapter* obj = (HotplugEventAdapter*)(user_data);
    obj->process_hotplug_event(event, dev, desc.idVendor, desc.idProduct, desc.iSerialNumber);
 
    return 0;
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

void HotplugEventAdapter::process_hotplug_event(int event_type, libusb_device* dev, int vendor, int product, int sn_idx) {
    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event_type) {
        hotplug_event(true, dev, vendor, product, sn_idx);        
    } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event_type) {
        hotplug_event(false, dev, vendor, product, sn_idx);
    }
}
