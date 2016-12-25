# testing module, to check understanding of modbus-tk with iCharger 4010 DUO USB HUD interface

import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
from modbus_tk.modbus import Query
from modbus_tk.modbus_rtu import RtuMaster
from modbus_tk.exceptions import ModbusInvalidRequestError, ModbusInvalidResponseError
from modbus_tk.utils import get_log_buffer

import usb.core
import usb.util
import struct

ICHARGER_VENDOR_ID = 0x483
ICHARGER_PRODUCT_ID = 0x5751
END_POINT_ADDRESS_WRITE = 0x01
END_POINT_ADDRESS_READ = 0x81
MAX_READWRITE_LEN = 64

#
# relies on the following going into /etc/udev/rules.d/10-icharger4010.rules
#
# apply user land permissions so we don't require root to read/write it
# SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5751", MODE:="0666"
#
#


class iChargerQuery(Query):
	"""
	Subclass of a Query. Adds the Modbus specific part of the protocol for iCharger over USB, which uses
	a specific protocol format to send the PDU.  Each read/write is limited to 64 bytes, whereby the PDU is 
	prefixed with two bytes, <ADU len> and 0x30 respectively.
	
	The 'slave' portion of the protocol goes unused because, I presume, the iCharger provides only a single modbus
	slave?
	"""

	def __init__(self):
		"""Constructor"""
		super(iChargerQuery, self).__init__()

	def build_request(self, pdu, slave):
		""" Constructs the output buffer for the request based on the func_code value """
		func_code = struct.unpack_from(">B", pdu[0])[0]
		adu_len = 99
		if func_code == cst.READ_INPUT_REGISTERS:
			adu_len = 7
		else:
			print("unknown func_code: %d, cannot calc length", func_code)
	
		assert adu_len != 99
		
		adu = struct.pack(">BB", adu_len, 0x30)

		#crc = struct.pack(">H", utils.calculate_crc(pdu))
		#return pdu + crc
		
		return adu + pdu

	def parse_response(self, response):
		if len(response) < 3:
			raise ModbusInvalidResponseError("Response length is invalid {0}".format(len(response)))

		(self.response_code, ) = struct.unpack(">B", response[2:1])

		# (crc, ) = struct.unpack(">H", response[-2:])

		# if crc != utils.calculate_crc(response[:-2]):
		# 	raise ModbusInvalidResponseError("Invalid CRC in response")

		return response[1:-2]


class USB:
	def __init__(self, vendorId, productId):
		self.dev = usb.core.find(idVendor=vendorId, idProduct=productId)
		if self.dev is None:
			return

		if not self._detach_kernel_driver():
			sys.exit("failed to detach kernel driver")

		# don't do this - fails every time on the Pi3.
		# self.dev.set_configuration()
		
		self.cfg = self.dev.get_active_configuration()

		self._claim_interface()
		
	def _detach_kernel_driver(self):
		if self.dev.is_kernel_driver_active(0):
			try:
				self.dev.detach_kernel_driver(0)
			except usb.core.USBError as e:
				return False
		return True
		
	def _claim_interface(self):
		try:
			usb.util.claim_interface(self.dev, 0)
			return True
		except:
			pass
		return False

	@property
	def serial_number(self):
		return usb.util.get_string(self.dev, self.dev.iSerialNumber) if self.valid else None
		
	@property
	def is_open(self):
		return self.dev is not None
		
	@property
	def name(self):
		if self.serial_number is not None:
			return "iCharger 4010 Duo SN:" + self.serial_number
		return "! iCharger Not Connected !"

	def open(self):
		# acquire the interface
		return True
	
	def close(self):
		# er, wot?
		return True
	
	@property
	def timeout(self):
		return 1000
		
	@timeout.setter
	def timeout(self, new_timeout):
		pass
		
	@property 
	def baudrate(self):
		return 19200
		
	@property
	def valid(self):
		return self.dev is not None

	def reset_input_buffer(self):
		pass
	
	def reset_output_buffer(self):
		pass
	
	def write(self, content):
		if self.dev is not None:
			pad_len = MAX_READWRITE_LEN - len(content)
			self.dev.write(END_POINT_ADDRESS_WRITE, content + ("\0" * pad_len))
		return 0
	
	def read(self, expected_length):
		return self.dev.read(END_POINT_ADDRESS_READ, expected_length).tostring()

	
class iChargerMaster(RtuMaster):
	def __init__(self, serial):
		super(iChargerMaster, self).__init__(serial)
		
	def _make_query(self):
		return iChargerQuery()


def main():
	logger = modbus_tk.utils.create_logger("console")

	master = iChargerMaster(USB(ICHARGER_VENDOR_ID, ICHARGER_PRODUCT_ID))

	master.set_timeout(10.0)
	master.set_verbose(True)
	
	res = master.execute(1, cst.READ_INPUT_REGISTERS, 0x0000, quantity_of_x=13, expected_length=26)
	print("got the data of type:", type(res))
	
	logger.info(res)
	
if __name__ == "__main__":
	main()


