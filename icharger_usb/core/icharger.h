
#ifndef __ICHARGER_USB_INTF
#define __ICHARGER_USB_INTF

#include <QSharedPointer>
#include <QList>

class USB_iCharger;
typedef QSharedPointer<USB_iCharger> USB_iChargerPtr;
typedef QList<USB_iChargerPtr> USB_iChargerPtrList;

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

private:
	class Private;
	Private* _p;
};

#endif

