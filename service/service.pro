
TEMPLATE = app
QT += network
QT -= gui

OBJECTS_DIR=build/obj

CONFIG += console
CONFIG -= app_bundle
CONFIG += debug

SOURCES = \
    main.cpp \
    usb/icharger_usb.cpp \
    bonjour/bonjourserviceregister.cpp \
    zmq/zmq_publisher.cpp \
    usb/eventhandler.cpp \
    usb/hotplug_adapter.cpp \
    device_registry.cpp \
    controller.cpp \ 
    message_handler.cpp

HEADERS = \ 
    bonjour\bonjourrecord.h \
    usb/icharger_usb.h \
    usb/icharger_data.h \
    util/singleton.h \
    bonjour/bonjourrecord.h \
    bonjour/bonjourserviceregister.h \
    zmq/zmq_publisher.h \
    usb/eventhandler.h \
    usb/hotplug_adapter.h \
    device_registry.h \
    controller.h \
    message_handler.h

unix:!macx {
    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0
    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev
}

macx {
    INCLUDEPATH += /usr/local/include /usr/local/include/libusb-1.0
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq 
}

TARGET = service

include (../3rdparty/nzmqt/nzmqt.pri)



