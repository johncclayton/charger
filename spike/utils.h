
#ifndef __UTILS_H
#define __UTILS_H

#include <libusb.h>
#include <memory>

void error_exit(const char* msg, int rc, ...);

struct usb_device;
typedef std::auto_ptr<usb_device> usb_device_ptr;

struct usb_device {
	libusb_device* device;
	libusb_device_handle* handle;
	bool is_open;

	usb_device(libusb_device* d);
	~usb_device();

	int usb_transfer(unsigned char endpoint_address,
                 	char* data,
                 	int length,
                 	int* total_transferred = 0,
                 	unsigned int timeout_ms = 1000);
	
	static usb_device_ptr first_charger(libusb_context* ctx, int vendor, int product);
};

#endif

