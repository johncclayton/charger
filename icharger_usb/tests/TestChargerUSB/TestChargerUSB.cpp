#include "TestChargerUSB.h"

void TestChargerUSB::setUp() {
}

void TestChargerUSB::test_usb_context_init() {
	QCOMPARE(true, _ctx.valid());
}

void TestChargerUSB::test_icharger_can_be_found() {
	USB_iChargerPtrList chargers = _ctx.chargers();	
	QVERIFY( chargers.size() > 0 );

	// ensure the product ID and vendor ID match
	USB_iChargerPtr icharger = chargers.first();	
}


