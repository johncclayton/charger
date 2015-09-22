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

	printf("size of device_only: %d\r\n", sizeof(device_only));

	libusb_set_debug(ctx, 4);

	{
        	icharger_usb_ptr device = icharger_usb::first_charger(ctx, ICHARGER_VENDOR_ID, ICHARGER_PRODUCT_ID);
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

		libusb_free_config_descriptor(config);

		struct device_only dev_only;
		memset(&dev_only, 0, sizeof(device_only));

		r = device->get_device_only(&dev_only);
		if(r == 0) {
			printf("device id : %d\r\n", dev_only.device_id.value);
			printf("device dn : %12s\r\n", dev_only.device_sn);
			printf("sw_version: %d\r\n", dev_only.sw_version.value);
			printf("hw_version: %d\r\n", dev_only.hw_version.value);
			printf("sys length: %d\r\n", dev_only.system_length.value);
			printf("mem length: %d\r\n", dev_only.memory_length.value);
			printf("ch1 state : %d\r\n", dev_only.ch1_status.value);
			printf("ch2 state : %d\r\n", dev_only.ch2_status.value);
	
		} else {
			printf("got error code: %d\r\n", r);
		}

		struct channel_status status;
		memset(&status, 0, sizeof(status));
	
		r = device->get_channel_status(1, &status);
		if(r == 0) {
			printf("Channel Status\r\n");
			printf("timestamp      : %ld\r\n", status.timestamp.value);

			printf("output pwr     : %ld\r\n", status.output_power.value);
			printf("output current : %ld\r\n", status.output_current.svalue);

			printf("input voltage  : %ld\r\n", status.input_voltage.value);
			printf("output voltage : %ld\r\n", status.output_voltage.value);
			printf("output capacity: %ld\r\n", status.output_capacity.value);

			printf("internal temp  : %ld\r\n", status.temp_internal.value);
			printf("external temp  : %ld\r\n", status.temp_external.value);

			for(int i = 0; i < MAX_CELLS; ++i) {
				printf("%d: cell voltage   : %ld\r\n", i, status.cell_voltage[i]);
				printf("%d: cell balance   : %d\r\n", i, status.balance_status[i]);
				printf("%d: cell resistance: %ld\r\n", i, status.cell_resistance[i]);
			}

			printf("total resistance: %ld\r\n", status.total_resistance);
			printf("line resistance : %ld\r\n", status.line_internal_resistance);

			printf("cycle count     : %ld\r\n", status.cycle_count);
			printf("control status  : %ld\r\n", status.control_status);
			printf("run status      : %ld\r\n", status.run_status);
			printf("run error       : %ld\r\n", status.run_error);
			printf("dialog box id   : %ld\r\n", status.dialog_box_id);
		} else {
			printf("unable to fetch the status of channel 1\r\n");
		}

		struct system_storage sys_storage;
		memset(&sys_storage, 0, sizeof(sys_storage));
		r = device->get_system_storage(&sys_storage);
		if(r == 0) {
			printf("System Storage\r\n");
			printf("unit temp           : %d\r\n", sys_storage.temp_unit);	
			printf("temp cut off        : %d\r\n", sys_storage.temp_cut_off);	
			printf("temp fans on        : %d\r\n", sys_storage.temp_fans_on);	
			printf("temp power reduce   : %d\r\n", sys_storage.temp_power_reduce);	
			printf("fans off delay      : %d\r\n", sys_storage.fans_off_delay);	
			printf("lcd_contrast        : %d\r\n", sys_storage.lcd_contrast);	
			printf("backlight value     : %d\r\n", sys_storage.backlight_value);	
			printf("calibration         : %d\r\n", sys_storage.calibration);	
			printf("input source        : %d\r\n", sys_storage.input_source);	
			
			printf("dc input low volt   : %d\r\n", sys_storage.dc_input_low_volt);	
			printf("dc input over volt  : %d\r\n", sys_storage.dc_input_over_volt);	
			printf("dc input curr limit : %d\r\n", sys_storage.dc_input_current_limit);	

			printf("bat input low volt  : %d\r\n", sys_storage.batt_input_low_volt);	
			printf("bat input over volt : %d\r\n", sys_storage.batt_input_over_volt);	
			printf("bat input curr limit: %d\r\n", sys_storage.batt_input_current_limit);	

			printf("regen enabled       : %d\r\n", sys_storage.regenerative_enable);
			printf("regen volt limit    : %d\r\n", sys_storage.regenerative_volt_limit);
			printf("regen curr limit    : %d\r\n", sys_storage.regenerative_current_limit);

			for(int i = 0; i < MODEL_MAX; ++i) {
				printf("%d: charger power   : %d\r\n", i, sys_storage.charger_power[i]);
				printf("%d: discharge powe  : %d\r\n", i, sys_storage.discharge_power[i]);
			}

			printf("power priority      : %d\r\n", sys_storage.power_priority);
			printf("logging sample rate : %d\r\n", sys_storage.logging_sample_interval);
			printf("logging save to sd  : %d\r\n", sys_storage.logging_save_to_sdcard);

			printf("servo type          : %d\r\n", sys_storage.servo_type);
			printf("servo user center   : %d\r\n", sys_storage.servo_user_center);
			printf("servo user rate     : %d\r\n", sys_storage.servo_user_rate);
			printf("servo user op angle : %d\r\n", sys_storage.servo_user_op_angle);
			 
			printf("modbus model        : %d\r\n", sys_storage.modbus_model);
			printf("modbus serial addr  : %d\r\n", sys_storage.modbus_serial_addr);
			printf("modbus server baud  : %d\r\n", sys_storage.modbus_serial_baud_rate);
			printf("modbus serial parity: %d\r\n", sys_storage.modbus_serial_parity_bits);
		} else {
			printf("unable to fetch the system storage data\r\n");
		}
	}

	libusb_exit(ctx);

	return 0;
}
