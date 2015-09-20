#!/bin/bash
gcc -I/usr/local/include/modbus -I/usr/include/libusb-1.0 -L/usr/local/lib -o read_test read_test.cpp -lstdc++ -lusb-1.0 -lmodbus && ./read_test
