#include "icharger_controller.h"
#include "usb/icharger_data.h"

iCharger_DeviceController::iCharger_DeviceController(Publisher_ptr pub, icharger_usb_ptr p, QObject *parent) : 
    QObject(parent), _pub(pub), _device(p)
{
    // query status of every bloody thing every second
    startTimer(500 /* ms */);
}

void iCharger_DeviceController::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    
    // fetch device status and publish on the bus
    device_only device;
    int r = _device->get_device_only(&device);
    if(r == 0) {
        // consert to JSON and make the unit sane.
        
    }           
}
