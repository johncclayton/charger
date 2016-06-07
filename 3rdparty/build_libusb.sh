#!/usr/bin/env bash

D=libusb-1.0.20
T=$D.tar
F=$T.bz2
B=$PWD/build

if [ ! -f "$F" ]; then
	wget http://downloads.sourceforge.net/project/libusb/libusb-1.0/libusb-1.0.20/libusb-1.0.20.tar.bz2
fi

if [ -d "$D" ]; then
	rm -rf "$D"
fi

if [ ! -f "$T" ]; then
	bunzip2 $F 
fi

tar xf $T && cd $D && ./configure --host=arm-linux-gnueabihf --enable-static --disable-udev --disable-shared --prefix=$B && make && make install
