Introduction
============

Typically I have the iCharger plugged into a Raspberry Pi 3, and I develop either on a Windows or Mac laptop.

The code runs as a series of microservices using Docker for deployment.

Checking in code on a laptop in order to pull it via Git into the runtime environment is a total pain, therefore I am
 using syncthing to keep code in sync between multiple dev devices and the runtime world of Docker.

Syncthing is an opensource multi-master synchronisation service that runs on almost anything (yay), and is secure (yay),
but it a pain in the butt to set up (boo).  Enter the tools in the syncthing/ directory to help with this (yay).

To get a dev system up and running, you will need:
 - a dev laptop - anything, Mac/Windows will do
 - a runtime device + an iCharger 4010 Duo

Syncthing Preparation
---------------------

Syncthing uses PKI technology to identify endpoints (machines/devices).  To setup the development environment you will
need the following identities:
 - Raspberry Pi 3 machine, that runs Docker, name: charger
 - Dev machine, that is Win or Mac, name: dev-host

Generate a syncthing identity for each device.  All identities are included the config for the syncthing service.  If
you create a new identity afterwards, you will need to re-create the docker images for each deployment device/context.

Create deployment images for the services, these get baked into the docker runtime images

Deploy and enjoy - everything just works because syncthing uses Dynamic lookup.






THE OLD INTERFACE

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


