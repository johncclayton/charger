
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
typedef QList<icharger_usb_ptr> charger_list;

#define ICHARGER_VENDOR_ID 0x483
#define ICHARGER_PRODUCT_4010_DUO 0x5751

/**
 * @brief The usb_context struct is a simple RAII wrapper around the libusb_context - its expected
 * that there is only a single one of these in the app.  
 * @see AppController.
 */
struct usb_context { 
	usb_context();
	~usb_context();

	libusb_context* ctx;
	int result;

	operator bool () {
		return result == 0;
	}
};

/**
 * @brief The icharger_usb struct is the actual device controller - it implements the required
 * MODBUS protocol over USB-HID by using libusb.  It is instantiated after the DeviceRegistry
 * uses the all_chargers method to find a recognized charger.
 */
struct icharger_usb {
    icharger_usb(libusb_device* d);
    ~icharger_usb();
   
    int acquire();
 
    int vendorId() const;
    int productId() const;
    
    // uses the device descriptor index to get the serial number
    QString serial_number();
    
    ModbusRequestError get_device_only(device_only* output);	
    ModbusRequestError get_channel_status(int channel /* 0 or 1 */, channel_status* output);
    ModbusRequestError get_system_storage(system_storage* output);
    ModbusRequestError order(OrderAction action, Channel ch, ProgramType pt, int selected_mem_index);
    
    static charger_list all_chargers(libusb_context* ctx, int vendor, int product, QString serial = QString());
    
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

