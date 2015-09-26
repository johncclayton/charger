
TEMPLATE = app
QT -= gui
QT += network

OBJECTS_DIR=build/obj

CONFIG += console
CONFIG -= app_bundle
CONFIG += debug

SOURCES = \
    main.cpp \
    usb/icharger_usb.cpp \
    bonjour/bonjourserviceregister.cpp \
    usb/eventhandler.cpp \
    usb/hotplug_adapter.cpp \
    device_registry.cpp \
    message_handler.cpp \
    zmq/socketbase.cpp \
    app_controller.cpp \
    icharger_controller.cpp \
    zmq/publisher.cpp \
    usb/icharger_data.cpp

HEADERS = \ 
    bonjour\bonjourrecord.h \
    usb/icharger_usb.h \
    usb/icharger_data.h \
    util/singleton.h \
    bonjour/bonjourrecord.h \
    bonjour/bonjourserviceregister.h \
    usb/eventhandler.h \
    usb/hotplug_adapter.h \
    device_registry.h \
    message_handler.h \
    zmq/socketbase.h \
    app_controller.h \
    icharger_controller.h \
    zmq/publisher.h

TARGET = service

unix:!macx {
    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0 
#    INCLUDEPATH += /usr/include/qjson
    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev -lqjson
}

macx {
    INCLUDEPATH += /usr/local/include 
#    INCLUDEPATH += /usr/local/include/qjson 
    INCLUDEPATH += /usr/local/include/libusb-1.0
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq -lqjson
}

include (../3rdparty/nzmqt/nzmqt.pri)



