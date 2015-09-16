import usb.core
import usb.util
import sys
from collections import namedtuple
from struct import *

DeviceDataFormat = '>H12cHHHHHH'
DeviceData = namedtuple('DeviceData', 'device_id device_dn sw_ver hw_ver sys_len mem_len ch1_status ch2_status')

# MODBUS READ from DEVICE 
def modbus_read_device(dev):
	pass

# find the iCharger 4010 Duo interface
VENDOR=0x0483
PRODUCT=0x5751

DEVICE_OFFSET=0x0000
WRITE_ENDPOINT=0x1
READ_ENDPOINT=0x81

def read_device_data(in_endpoint):
	bytes = '	

dev = usb.core.find(idVendor=VENDOR, idProduct=PRODUCT)
if dev is None:
	print "No devices!"
else:
	# get the first interface - it's NOT the mass storage one
	cfg = dev[0]
	iface = cfg[(0, 0)]
	data_in = iface[0]
	data_out = iface[1]

	read_device_data(data_in)
