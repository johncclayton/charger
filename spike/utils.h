
#ifndef __UTILS_H
#define __UTILS_H

#include <libusb.h>

void error_exit(const char* msg, int rc, ...);

libusb_device* first_charger(libusb_context* ctx, int vendor, int product);

int usb_transfer(libusb_device_handle *handle,
                 unsigned char endpoint_address,
                 char* data,
                 int length,
                 int* total_transferred = 0,
                 unsigned int timeout_ms = 1000);

#endif

