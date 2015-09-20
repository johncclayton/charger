#include <stdarg.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void error_exit(const char* msg, int rc, ...) {
        char buffer[2048];
        memset(buffer, 0, sizeof(buffer));

        va_list args;
        va_start(args, rc);
        vsprintf(buffer, msg, args);
        va_end(args);

        printf("%s, %d/%s\r\n", buffer, rc, libusb_error_name(rc));

        exit(1);
}

libusb_device* first_charger(libusb_context* ctx, int vendor, int product) {
        libusb_device **devs;
        size_t cnt = libusb_get_device_list(ctx, &devs);

        libusb_device* found = 0;

        for(size_t index = 0; index < cnt && !found; ++index) {
                struct libusb_device_descriptor desc;
                int r = libusb_get_device_descriptor(devs[index], &desc);
                if (r >= 0) {
                        if(desc.idVendor == vendor &&
                           desc.idProduct == product) {
                                found = devs[index];
                        }
                }
        }

        if(found)
                libusb_ref_device(found);

        libusb_free_device_list(devs, 1 /* unref all elements please */);

        return found;
}

/* same as the library version, but automatically handles retry on timeout */
int usb_transfer(libusb_device_handle *handle,
                 unsigned char endpoint_address,
                 char* data,
                 int length,
                 int* total_transferred,
                 unsigned int timeout_ms)
{
        int r = 0;

	int temp_total = 0;
	if(!total_transferred)
		total_transferred = &temp_total;

	printf("length value is: %d\r\n", length);

        int bytes_transferred = 0;
        char* data_ptr = data;

        while(1) {
                int transferred = 0;

                r = libusb_interrupt_transfer(
                                        handle,
                                        endpoint_address,
                                        (unsigned char *)data + bytes_transferred,
                                        length - bytes_transferred,
                                        &transferred,
                                        timeout_ms);

		
                *total_transferred += transferred;
                printf("op %d, transferred bytes: %d, last result: %d/%s\r\n", 
			endpoint_address, 
			*total_transferred, 
			r, 
			libusb_error_name(r));

                if(r == LIBUSB_ERROR_TIMEOUT) {
                        printf("retrying...\r\n");
                } else if(r != 0) {
                        error_exit("an error was encountered during data transfer", r);
                }

                if(*total_transferred >= length)
                        return 0;
        }
}

