
import usb.core
import usb.util

ICHARGER_VENDOR_ID = 0x483
ICHARGER_PRODUCT_ID = 0x5751

class iChargerDevice(object):
    def __init__(self):
        self.dev = usb.core.find(idVendor=ICHARGER_VENDOR_ID, idProduct=ICHARGER_PRODUCT_ID)
        if self.dev is None:
            return

        # self.dev.set_configuration()
        self.cfg = self.dev.get_active_configuration()

    @property
    def valid(self):
        return self.dev is not None

    @property
    def serial_number(self):
        return usb.util.get_string(self.dev, self.dev.iSerialNumber) if self.valid else None

    @property
    def manufacturer(self):
        return usb.util.get_string(self.dev, self.dev.iManufacturer) if self.valid else None

    @property
    def product_name(self):
        return usb.util.get_string(self.dev, self.dev.iProduct) if self.valid else None

