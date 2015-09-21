#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

#include "utils.h"

#define ICHARGER_VENDOR_ID 0x0483
#define ICHARGER_PRODUCT_ID 0x5751

libusb_context* ctx = 0;

int main(int argc, char *argv[]) {
	int r = libusb_init(&ctx);
	if(r != 0)
		error_exit("failed to init libusb", r);

	libusb_set_debug(ctx, 4);

        usb_device_ptr device = usb_device::first_charger(ctx, ICHARGER_VENDOR_ID, ICHARGER_PRODUCT_ID);
	if(! device.get())
		error_exit("cannot find an iCharger device", -1);

	if(libusb_kernel_driver_active(device->handle, 0) == 1) {
		printf("the kernel has claimed this device, asking to detach it... ");
		if(libusb_detach_kernel_driver(device->handle, 0) == 0)
			printf("detached\r\n");
		else
			error_exit("unable to detach the kernel from the device", 0);
	}

	int configuration = 0;
	r = libusb_get_configuration(device->handle, &configuration);
	if(r != 0) {
		error_exit("cannot obtain the current configuration: %d", r);
	}

	printf("active configuration: %d\r\n", configuration);

 	r = libusb_claim_interface(device->handle, 0); 
   	 if(r < 0) 
       		error_exit("cannot claim the interface, err: %d", r);

	// find the right interface, it's the non-SD card one...a HID type.	
	struct libusb_config_descriptor * config = 0;
	r = libusb_get_active_config_descriptor(device->device, &config);
	if(r != 0) {
		error_exit("cannot obtain the current configuration description", r);
	}

	struct device_only dev_only;
	memset(&dev_only, 0, sizeof(device_only));
	printf("size of bytes for device_only: %d\r\n", sizeof(dev_only));

	if(0 == device->get_device_only(&dev_only)) {
		printf("I did something\r\n");
	}

	libusb_free_config_descriptor(config);
	libusb_exit(ctx);

	return 0;
}
