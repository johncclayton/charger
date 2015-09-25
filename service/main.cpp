#include <QCoreApplication>
#include "controller.h"

// The app will run as a daemon process, accepting requests to do stuff via ZeroMQ.  These requests are 
// simply passed into the USB device that represents the charger. 
//
// Current status of the device, it's channels and so on is published continuously on the ZeroMQ pub/sub
// bus.
// 
// ALL configuration is via Bonjour - the app will publish its services there. 

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    try {
    	Controller main_controller;
    main_controller.init();
    return app.exec();
}
