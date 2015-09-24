#include "usb/usb_hotpluglistener.h"
#include "libusb.h"

int hotplug_callback(struct libusb_context *ctx, 
                     struct libusb_device *dev,
                     libusb_hotplug_event event, 
                     void *user_data) 
{
//    struct libusb_device_descriptor desc;
//    libusb_get_device_descriptor(dev, &desc);
    
    USB_HotPlugListener* obj = (USB_HotPlugListener*)(user_data);
    obj->process_hotplug_event(event);
 
    return 0;
}

struct USB_HotPlugListener::Private {
    libusb_hotplug_callback_handle handle;
    
    Private() : handle(0) {
        
    }
};

USB_HotPlugListener::USB_HotPlugListener(void* ctx, QObject *parent) : QObject(parent), _p(new Private)
{
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

USB_HotPlugListener::~USB_HotPlugListener() {
    libusb_hotplug_deregister_callback(NULL, _p->handle);
    delete _p;
}

void USB_HotPlugListener::process_hotplug_event(int event_type) {
    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event_type) {
        hotplug_event(true);        
    } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event_type) {
        hotplug_event(false);
    }
}
