Prerequisites: 
- q4 + dev tools
- libsodium
- zeromq

I installed libsodium then zeromq from the net.  The cppzmg library that comes with nzmqt is old and errors out due to missing zmq_event_t type - go get the latest single cppzmq.hpp from git and replace the file in 3rdparty/include.


