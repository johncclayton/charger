#ifndef USB_HOTPLUGLISTENER_H
#define USB_HOTPLUGLISTENER_H

struct libusb_context;

/**
 * @brief The HotplugEventAdapter class is responsible to matching hotplug events to the USB driver code 
 * for each known device.  When a hotplug event is detected for a device we know about, the serial number
 * of the devic is obtained and a callback is fired indicating whether the device was attached or removed.
 * 
 * The serial number is only obtained for attachment events.
 */
class HotplugCallbackAdapter 
{
public:
    struct Receiver {
        virtual void callback(bool activation, int vendorId, int productId, QString sn) = 0;
    };

    explicit HotplugCallbackAdapter(Receiver* func);
    virtual ~HotplugCallbackAdapter();
    
    void init(libusb_context* ctx);    
    void process_hotplug_event(int event_type, int vendor, int product, QString sn);
        
private:
    struct Private;
    Private* _p;
};

#endif // USB_HOTPLUGLISTENER_H
