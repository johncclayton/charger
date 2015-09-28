TEMPLATE = app
QT -= gui
QT += network

OBJECTS_DIR=build/obj

CONFIG += console
CONFIG -= app_bundle
CONFIG += debug

SOURCES = \
    main.cpp \
    app_controller.cpp \
    device_registry.cpp \
    message_handler.cpp \
    bonjour/bonjourserviceregister.cpp \
    icharger_controller.cpp \
    usb/icharger_data.cpp \
    usb/icharger_usb.cpp \
    usb/eventhandler.cpp \
    usb/hotplug_adapter.cpp \
    zmq/socketbase.cpp \
    zmq/publisher.cpp

HEADERS = \ 
    app_controller.h \
    device_registry.h \
    icharger_controller.h \
    message_handler.h \
    bonjour\bonjourrecord.h \
    bonjour/bonjourserviceregister.h \
    usb/icharger_usb.h \
    usb/icharger_data.h \
    usb/eventhandler.h \
    usb/hotplug_adapter.h \
    util/singleton.h \
    zmq/socketbase.h \
    zmq/publisher.h

TARGET = service

unix:!macx {
    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0 
    INCLUDEPATH += /usr/include/qjson
    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev -lqjson
}

macx {
    INCLUDEPATH += /usr/local/include 
    INCLUDEPATH += /usr/local/include/qjson 
    INCLUDEPATH += /usr/local/include/libusb-1.0 
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq 
}

include (../3rdparty/nzmqt/nzmqt.pri)



