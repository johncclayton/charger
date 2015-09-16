#include "icharger.h"

#include <libusb.h>
#include <iostream>

const int ICHARGER_VENDOR = 0x0483;
const int ICHARGER_4010DUO_PRODUCT_ID = 0x5751;

struct USBContext::Private {
	libusb_context *ctx;

	Private() {
		libusb_init(&ctx);
	}

	~Private() {
		Q_ASSERT(ctx != 0);
        	libusb_exit(ctx);
		ctx = 0;
	}
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

struct USB_iCharger::Private {
	libusb_device* device;

	Private() : device(0) {
	}

	void unassign_device() {
		if(device)
			libusb_unref_device(device);
		device = 0;
	}

	void assign_device(libusb_device* device_to_own) {
		unassign_device();	
		device = libusb_ref_device(device_to_own);
	}

	~Private() {
		unassign_device();
	}
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

USBContext::USBContext() : _p(0) {
	_p = new Private();
	libusb_set_debug(_p->ctx, 3);
}

USBContext::~USBContext() {
	delete _p;
	_p = 0;
}

bool USBContext::valid() const {
	return _p->ctx != 0;
}

USB_iChargerPtrList USBContext::chargers() {
	Q_ASSERT(_p);
	Q_ASSERT(_p->ctx);

	USB_iChargerPtrList ichargers;
	// find all devices with the right vendor/identifier

	libusb_device **devs;
	size_t cnt = libusb_get_device_list(_p->ctx, &devs);
	for(size_t index = 0; index < cnt; ++index) {
		libusb_device_descriptor desc;
    		int r = libusb_get_device_descriptor(devs[index], &desc);
    		if (r >= 0) {
			if(desc.idVendor == ICHARGER_VENDOR &&
                           desc.idProduct == ICHARGER_4010DUO_PRODUCT_ID) {
				USB_iChargerPtr obj(new USB_iCharger());
				obj->_p->assign_device(devs[index]);
				ichargers.push_back(obj);
			}
    		}
	}

	libusb_free_device_list(devs, 1);

	return ichargers;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

USB_iCharger::USB_iCharger() : _p(0) {
	_p = new Private();
}

USB_iCharger::~USB_iCharger() {
	delete _p;
}
