
#ifndef __ICHARGER_USB_INTF
#define __ICHARGER_USB_INTF

#include <QSharedPointer>
#include <QList>

class USB_iCharger;
typedef QSharedPointer<USB_iCharger> USB_iChargerPtr;
typedef QList<USB_iChargerPtr> USB_iChargerPtrList;

#define ICHARGER_VENDOR_ID 0x0483
#define ICHARGER_PRODUCT_ID 0x5751

class USBContext { 
public:
	USBContext();
	virtual ~USBContext();

	bool valid() const;
	USB_iChargerPtrList chargers();

private:
	class Private;
	Private* _p;
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class USB_iCharger {
	friend class USBContext;

public:
	USB_iCharger();
	virtual ~USB_iCharger();

	bool connected() const { return false; }
	int configuration() const;
	int vendorID() const;
	int productID() const;

private:
	class Private;
	Private* _p;
};

#endif

