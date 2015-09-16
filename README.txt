Prerequisites: 
- q4 + dev tools
- libsodium
- zeromq

I installed libsodium then zeromq from the net.  The cppzmg library that comes with nzmqt is old and errors out due to missing zmq_event_t type - go get the latest single cppzmq.hpp from git and replace the file in 3rdparty/include.

Arch
----

Everything hangs together based on ZeroMQ.  This allows me to write the components in whatever language I want, applicable to the task at hand. 

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

