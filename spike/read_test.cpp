#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

#include "utils.h"

#define ICHARGER_VENDOR_ID 0x0483
#define ICHARGER_PRODUCT_ID 0x5751

#define END_POINT_ADDRESS_WRITE 0x01
#define END_POINT_ADDRESS_READ 0x81

libusb_context* ctx = 0;

#pragma pack(1)

typedef unsigned long   u32;
typedef signed long     s32;
typedef unsigned short  u16;
typedef signed short    s16;
typedef unsigned char   u8;
typedef signed char     s8;

union data_register {
	u16 word;
	struct {
		u8 high;
		u8 low;
	};
};

// available at base address: 0x0000
struct device_only {
	data_register	device_id;
	s16		device_dn[12];
	data_register 	sw_version;
	data_register	hw_version;
	data_register	system_length;
	data_register	memory_length;
	data_register	ch1_status;
	data_register	ch2_status;	
};

struct request {
	u8 func_code;
	request(char fc) : func_code(fc) {}
};

struct read_data_registers : public request {
	data_register starting_address;
	data_register quantity_to_read;

	read_data_registers(int base_addr, int num_registers) : request(0x04) {
		starting_address.high = base_addr >> 8;
		starting_address.low = base_addr & 0xff;
		quantity_to_read.high = num_registers >> 8;
		quantity_to_read.low = num_registers & 0xff;
	}
};

struct response_header : public request {
	unsigned char byte_count;
	response_header() : request(0) {}
};

int modbus_request(usb_device_ptr usb, char func_code, int base_addr, int num_registers, char* dest) {
	// preps the request in mem (the PDU)
	read_data_registers read_req(base_addr, num_registers);

	// now create the modbus ADU
	char data [64];
	memset(data, 0, sizeof(data));

	data[0] = 7;
	data[1] = 0x30;
	memcpy(data + 2, &read_req, sizeof(read_req));
	
	int r = usb->usb_transfer(END_POINT_ADDRESS_WRITE, data, sizeof(data));					  
	if(r != 0) {
		error_exit("didnt write all of the request data", r);
	} else {
		response_header header;
		if(usb->usb_transfer(END_POINT_ADDRESS_READ, (char *)&header, 2) == 0) {
			printf("response payload has %d bytes in it\r\n", header.byte_count);
			char *reply_payload = new char [header.byte_count];
			r = usb->usb_transfer(END_POINT_ADDRESS_READ, reply_payload, header.byte_count);
			if(r == 0) {
				printf("reply received!\r\n");
			}

			delete [] reply_payload;
		}
	}

	return -1;
}

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

 	r = libusb_claim_interface(device->handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
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

	if(modbus_request(device, 0x04 /* read only */, 0x0000, sizeof(device_only), (char*)&dev_only))
		printf("failed to read modbus information for device only read area\r\n");
	else {
		printf("I did something\r\n");
	}

	libusb_free_config_descriptor(config);
	libusb_exit(ctx);

	return 0;
}
