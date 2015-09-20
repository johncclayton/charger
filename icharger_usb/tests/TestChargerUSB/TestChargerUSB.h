#include <QtTest/QtTest>

#include "icharger.h"

class TestChargerUSB : public QObject {

Q_OBJECT

private slots: 
	void setUp();
	void test_usb_context_init();
	void test_icharger_can_be_found();
	void test_configuration_state();
	void test_read_system();

private:
	USBContext _ctx;
};

