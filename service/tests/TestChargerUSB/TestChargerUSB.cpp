#include <QDebug>
#include "TestChargerUSB.h"
#include "icharger_msg.h"

void TestChargerUSB::setUp() {
	qDebug() << "size of SYSTEM message:" << sizeof(SYSTEM);
}

void TestChargerUSB::test_usb_context_init() {
	QCOMPARE(true, _ctx.valid());
}

USB_iChargerPtr getFirstICharger(USBContext& ctx) {
	USB_iChargerPtrList chargers = ctx.chargers();	
	if(chargers.empty())
		return USB_iChargerPtr();
	return chargers.first();	
}

void TestChargerUSB::test_icharger_can_be_found() {
	// test that a blank context returns empty charger ptr
	USB_iChargerPtrList empty;
	QVERIFY( empty.empty() );
	
	USB_iChargerPtrList chargers = _ctx.chargers();	
	QVERIFY( chargers.size() > 0 );

	// ensure the product ID and vendor ID match
	USB_iChargerPtr icharger = chargers.first();	
	QVERIFY( icharger );
	
	QCOMPARE( ICHARGER_PRODUCT_ID, icharger->productID() );
	QCOMPARE( ICHARGER_VENDOR_ID, icharger->vendorID() );
}

void TestChargerUSB::test_configuration_state() {
	USB_iChargerPtr icharger = getFirstICharger(_ctx);	
	qDebug() << "configuration is: " << icharger->configuration();
}

void TestChargerUSB::test_read_system() {
}
