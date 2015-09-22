
#ifndef __UTILS_H
#define __UTILS_H

#include <libusb.h>
#include <memory>

void error_exit(const char* msg, int rc, ...);

struct usb_device;
typedef std::auto_ptr<usb_device> usb_device_ptr;

typedef enum
{
    MB_EOK = 0x00,				/*!< no error. */
    MB_EX_ILLEGAL_FUNCTION = 0x01,
    MB_EX_ILLEGAL_DATA_ADDRESS = 0x02,
    MB_EX_ILLEGAL_DATA_VALUE = 0x03,
    MB_EX_SLAVE_DEVICE_FAILURE = 0x04,
    MB_EX_ACKNOWLEDGE = 0x05,
    MB_EX_SLAVE_BUSY = 0x06,
    MB_EX_MEMORY_PARITY_ERROR = 0x08,
    MB_EX_GATEWAY_PATH_FAILED = 0x0A,
    MB_EX_GATEWAY_TGT_FAILED = 0x0B,
    MB_ENOREG = 0x80,  			        /*!< illegal register address. */
    MB_EILLFUNCTION,				/*!< illegal function code. */
    MB_EIO,                     		/*!< I/O error. */
    MB_ERETURN,					/*!< protocol stack in illegal state. */
    MB_ELEN,					/*!< pack len larg error. */
    MB_ETIMEDOUT                		/*!< timeout error occurred. */
} eMBErrorCode;

typedef unsigned long   u32;
typedef signed long     s32;
typedef unsigned short  u16;
typedef signed short    s16;
typedef unsigned char   u8;
typedef signed char     s8;

union register16 {
        u16 value;
        struct {
                u8 high;
                u8 low;
        } __attribute__ ((packed));
} __attribute__ ((packed));

union register32 {	
	u32 value;	
	struct {
		register16 high;
		register16 low;
	} __attribute__ ((packed));
} __attribute__ ((packed));	

// available at base address: 0x0000
struct device_only {
        register16   device_id;
        s8           device_dn[12];
        register16   sw_version;
        register16   hw_version;
        register16   system_length;
        register16   memory_length;
        register16   ch1_status;
        register16   ch2_status;
} __attribute__ ((packed));

// available at 0x0100 and 0x0200 (ch1 and ch2)
struct channel_status {
	register32 timestamp;
	register32 ouput_power;
	register16 output_current;
	register16 input_voltage;
	register16 output_voltage;
	register32 output_capacity;

	register16 temp_internal;
	register16 temp_external;

	u16 cell_voltage[16];
	u8 balance_status[16];
	u16 cell_resistance[16];
	u16 total_resistance;

	u16 line_internal_resistance;
	u16 cycle_count;	
	u16 control_status;
	u16 run_status;
	u16 run_error;
	u16 dialog_box_id;
} __attribute__ ((packed));

struct read_data_registers {
        register16 starting_address;
        register16 quantity_to_read;

        read_data_registers(int base_addr, int num_registers) {
                starting_address.high = base_addr >> 8;
                starting_address.low = (char)(base_addr & 0xff);
                quantity_to_read.high = num_registers >> 8;
                quantity_to_read.low = (char)(num_registers & 0xff);
        }
} __attribute__ ((packed));

struct usb_device {
	libusb_device* device;
	libusb_device_handle* handle;
	bool is_open;	
	int timeout_ms;

	usb_device(libusb_device* d);
	~usb_device();

	int get_device_only(device_only* output);	
	
	static usb_device_ptr first_charger(libusb_context* ctx, int vendor, int product);

private:
	int usb_data_transfer(unsigned char endpoint_address,
                                  char* data,
                                  int length,
                                  int* total_transferred = 0);

	int modbus_request(char func_code, char* input, char *output);
	int read_request(char func_code, int base_addr, int num_registers, char* dest);
	int write_request(char func_code, int base_addr, int num_registers, char* dest);
};

#endif

