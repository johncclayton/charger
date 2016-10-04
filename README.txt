Prerequisites: 
- libusb - compiled via 3rdparty directory
- q4 + dev tools
- libsodium
- zeromq

I installed libsodium then zeromq from the net.  The cppzmg library that comes with nzmqt is old and errors out due to missing zmq_event_t type - go get the latest single cppzmq.hpp from git and replace the file in 3rdparty/include.

Arch
----

Everything hangs together based on ZeroMQ.  This allows me to write the components in whatever language I want, applicable to the task at hand. 

Compiling libusb
================
Install libudev via this:
    apt-get install libudev0



USB Interface
=============
The iCharger communicates via USB.  It's driven by the icharger_usb program that provides the following service end-points: 
	req/resp - settings & commands
	pub/sub - state of the device

For example, to get information about the iCharger system you would do the following:
	
	- connect to all zeromq end points
	- send an INIT_DONE request to the icharger_usb command interface
	- wait for a INIT_CONFIRMED response from the publisher, this contains the initial state snapshot

After this has been done, further state responses are received on the pub/sub bus as any data changes.  The frequencly of updates is controlled by 
the icharger_usb service. 

Installing the Raspian Image from Mac
=====================================

Go get Raspian from: https://www.raspberrypi.org/downloads/raspbian/

To overwrite the SD card (16 gig minimum), find the disk number (not partition):

diskutil list
diskutil unmountDisk /dev/disk2
sudo dd bs=1m if=<name of image>.img of=/dev/rdisk2

Boot the image and run:
  sudo raspi-config

Change it to boot to console instead of UI, change GPU mem to 256 MB.

Modify the apt sources to get Qt 5 - uncomment the deb-src line:
  sudo nano /etc/apt/sources.list

Then update apt:
  sudo apt-get update
  sudo apt-get build-dep qt4-x11
  sudo apt-get build-dep libqt5gui5
  sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev

  sudo mkdir /usr/local/qt5pi
  sudo chown pi:pi /usr/local/qt5pi


