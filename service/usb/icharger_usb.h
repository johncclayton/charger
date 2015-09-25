
#ifndef __ICHARGER_USB_H
#define __ICHARGER_USB_H

extern "C" {
    #include <libusb.h>
}

#include <QList>
#include <QSharedPointer>
#include <QStringList>

#include "icharger_data.h"

#include <memory>

void error_exit(const char* msg, int rc, ...);

struct icharger_usb;
typedef QSharedPointer<icharger_usb> icharger_usb_ptr;
typedef QStringList charger_serial_list;


struct usb_context { 
	usb_context();
	~usb_context();

	libusb_context* ctx;
	int result;

	operator bool () {
		return result == 0;
	}
};

struct icharger_usb {
    icharger_usb(libusb_device* d);
    ~icharger_usb();
   
    int acquire();
 
    ModbusRequestError get_device_only(device_only* output);	
    ModbusRequestError get_channel_status(int channel /* 0 or 1 */, channel_status* output);
    ModbusRequestError get_system_storage(system_storage* output);
    ModbusRequestError order(OrderAction action, Channel ch, ProgramType pt, int selected_mem_index);
    
    static charger_serial_list all_chargers(libusb_context* ctx, int vendor, int product);
    static icharger_usb_ptr first_charger(libusb_context* ctx, int vendor, int product);
    
private:
    libusb_device* device;
    libusb_device_handle* handle;
    int timeout_ms;
    
    int usb_data_transfer(unsigned char endpoint_address,
                          char* data,
                          int length,
                          int* total_transferred = 0);
    
    ModbusRequestError modbus_request(char func_code, char* input, char *output);
    ModbusRequestError read_request(char func_code, int base_addr, int num_registers, char* dest);
    ModbusRequestError write_request(int base_addr, int num_registers, char* dest);
};

#endif

