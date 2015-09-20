#include "icharger.h"

#include <libusb.h>
#include <iostream>

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
 	libusb_device_handle *handle;

	int configuration;

	Private() : device(0), handle(0), configuration(0) {
	}

	void unassign_device() {
		if(handle)
			libusb_close(handle);

		if(device)
			libusb_unref_device(device);

		device = 0;
		handle = 0;
		configuration = 0;
	}

	int assign_device(libusb_device* device_to_own) {
		unassign_device();	

		if(!device_to_own)
			return LIBUSB_ERROR_NO_DEVICE;

		device = libusb_ref_device(device_to_own);

		int r = libusb_open(device, &handle);
		if(r != 0)
			return r;

		if(handle) 
			r = libusb_get_configuration(handle, &configuration);

		return r;
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
			if(desc.idVendor == ICHARGER_VENDOR_ID &&
                           desc.idProduct == ICHARGER_PRODUCT_ID) {
				USB_iChargerPtr obj(new USB_iCharger());
				if(!obj->_p->assign_device(devs[index]))
					ichargers.push_back(obj);
			}
    		}
	}

	libusb_free_device_list(devs, 1 /* unref all elements please */);

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

int USB_iCharger::configuration() const { 
	return _p->configuration;
}

int USB_iCharger::vendorID() const {
	Q_ASSERT( _p->device );
	libusb_device_descriptor desc;
	if(!libusb_get_device_descriptor(_p->device, &desc))
		return desc.idVendor;
	return 0;
}

int USB_iCharger::productID() const {
	Q_ASSERT( _p->device );
	libusb_device_descriptor desc;
	if(!libusb_get_device_descriptor(_p->device, &desc))
		return desc.idProduct;
	return 0;
}

SYSTEM USB_iCharger::readSystem() const { 
	SYSTEM s;
	memset(&s, 0, sizeof(s));
	return s;
}

