#include <modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <memory.h>
#include <libusb.h>
#include <iostream>

#define ICHARGER_VENDOR_ID 0x0483
#define ICHARGER_PRODUCT_ID 0x5751

#define END_POINT_ADDRESS_WRITE 0x01
#define END_POINT_ADDRESS_READ 0x81

using namespace std;
libusb_context* ctx = 0;

#pragma pack(1)

typedef unsigned long   u32;
typedef signed long     s32;
typedef unsigned short  u16;
typedef signed short    s16;
typedef unsigned char   u8;
typedef signed char     s8;

// base address: 0x0000
typedef struct _device_only {
	u16 		device_id;
	s16		device_dn[12];
	u16		sw_version;
	u16		hw_version;
	u16		system_length;
	u16		memory_length;
	u16		ch1_status;
	u16		ch2_status;	
} DeviceOnly;

void error_exit(const char* msg, int exit_code) {
	printf("%s\r\n", msg);
	if(exit_code != 0)
		exit(exit_code);
}

libusb_device* first_charger() {
        libusb_device **devs;
        size_t cnt = libusb_get_device_list(ctx, &devs);

	libusb_device* found = 0;

        for(size_t index = 0; index < cnt && !found; ++index) {
                struct libusb_device_descriptor desc;
                int r = libusb_get_device_descriptor(devs[index], &desc);
                if (r >= 0) {
                        if(desc.idVendor == ICHARGER_VENDOR_ID &&
                           desc.idProduct == ICHARGER_PRODUCT_ID) {
				found = devs[index];
                        }
                }
        }

	if(found)
		libusb_ref_device(found);

        libusb_free_device_list(devs, 1 /* unref all elements please */);

        return found;
}

void printdev(libusb_device *dev) {
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        cout<<"failed to get device descriptor"<<endl;
        return;
    }

    cout<<"Number of possible configurations: "<<(int)desc.bNumConfigurations<<"  ";
    cout<<"Device Class: "<<(int)desc.bDeviceClass<<"  ";
    cout<<"VendorID: "<<desc.idVendor<<"  ";
    cout<<"ProductID: "<<desc.idProduct<<endl;

    libusb_config_descriptor *config;
    libusb_get_config_descriptor(dev, 0, &config);

    cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";
    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;

    for(int i=0; i<(int)config->bNumInterfaces; i++) {
        inter = &config->interface[i];
        cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";
        for(int j=0; j<inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";
            cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";
            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
                epdesc = &interdesc->endpoint[k];
                cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";
                cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";
            }
        }
    }
    cout<<endl<<endl<<endl;
    libusb_free_config_descriptor(config);
}

int modbus_request(libusb_device_handle* handle, char func_code, int base_addr, int num_words, char* dest) {
	unsigned char data [500];
	memset(data, 0, sizeof(data));

	char msg_length = 7;
	data[0] = msg_length;	
	data[1] = 0x30;
	data[2] = func_code;
	data[3] = (base_addr & 0xff00) >> 8; 
	data[4] = base_addr & 0x00ff;
	data[5] = (num_words & 0xff00) >> 8;
	data[6] = num_words & 0x00ff;

	int timeout_ms = 500;
	int transferred = 0;
	int r = libusb_interrupt_transfer(handle, 
					  END_POINT_ADDRESS_WRITE,
					  data, 
					  msg_length,
				          &transferred,
					  timeout_ms);					  

	// now read the response...
		
	
	return -1;
}

int main(int argc, char *argv[]) {
	if( libusb_init(&ctx) )
		error_exit("failed to init libusb", 1);

	libusb_set_debug(ctx, 3);

        libusb_device* device = first_charger();
	if(! device)
		error_exit("cannot find an iCharger device", 2);

	printdev(device);

	libusb_device_handle* handle = 0;
	int r = libusb_open(device, &handle);
	if(r != 0) {
		libusb_unref_device(device);
		error_exit("cannot open the device", 3);
	}

	if(libusb_kernel_driver_active(handle, 0) == 0) {
		printf("the kernel has claimed this device, asking to detach it... ");
		if(libusb_detach_kernel_driver(handle, 0) == 0)
			printf("detached\r\n");
		else
			printf("unable to detach!\r\n");
	}

 	r = libusb_claim_interface(handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
   	 if(r < 0) 
       		error_exit("cannot claim the interface", 8);

	int configuration = 0;
	r = libusb_get_configuration(handle, &configuration);
	if(r != 0) {
		libusb_close(handle);
		libusb_unref_device(device);
		error_exit("cannot obtain the current configuration", 4);
	}

	// find the right interface, it's the non-SD card one...a HID type.	
	struct libusb_config_descriptor * config = 0;
	r = libusb_get_active_config_descriptor(device, &config);
	if(r != 0) {
		libusb_close(handle);
		libusb_unref_device(device);
		error_exit("cannot obtain the current configuration description", 5);
	}

	for(int i = 0; i < config->bNumInterfaces; i++) {
		
	}

	DeviceOnly device_only;
	memset(&device_only, 0, sizeof(device_only));
	if(modbus_request(handle, 0x04 /* read only */, 0x0000, sizeof(DeviceOnly) / 2, (char*)&device_only))
		printf("failed to read modbus information for device only read area\r\n");
	else {
	}

	libusb_free_config_descriptor(config);
	libusb_close(handle);
	libusb_unref_device(device);

	libusb_exit(ctx);

	return 0;
}
