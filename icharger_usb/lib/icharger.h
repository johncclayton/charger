
#ifndef __ICHARGER_USB_INTF
#define __ICHARGER_UDB_INTF

#include <libusb.h>

class USBContext { 
public:
	USBContext() {
 		libusb_init(&_ctx);
	}

	~USBContext() {
		libusb_exit(_ctx);
	}

	libusb_context* operator() { return _ctx; }	

private:
	libusb_context* _ctx;
};

class IChargerUSB {

public:

private:
};

#endif

