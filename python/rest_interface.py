from flask_restful import Resource
from python.icharger.usb_device import iChargerDevice
import json

class Status_iCharger(Resource):
    def __init__(self):
        super(Status_iCharger, self).__init__()

    def get(self):
        dev = iChargerDevice()

        return {
            "found": dev.valid,
            "serial": dev.serial_number,
            "product": dev.product_name,
            "manufacturer": dev.manufacturer
            # "config": dev.cfg.__str__()
        }