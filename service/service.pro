TEMPLATE = app
QT -= gui
QT += network

CONFIG += console
CONFIG -= app_bundle

OBJECTS_DIR=build/obj
INCLUDEPATH += ../lib
LIBS += ../lib/libcore.a

SOURCES = \
    main.cpp \
    app_controller.cpp \
    device_registry.cpp \
    message_handler.cpp \
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
    usb/icharger_usb.h \
    usb/icharger_data.h \
    usb/eventhandler.h \
    usb/hotplug_adapter.h \
    util/singleton.h \
    zmq/socketbase.h \
    zmq/publisher.h 

TARGET = charger

unix:!macx {
    INCLUDEPATH += /usr/include/qjson
    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0 
    INCLUDEPATH += ../3rdparty/build/include 
    LIBS += ../3rdparty/build/lib/libusb-1.0.a 
    LIBS += ../3rdparty/build/lib/libzmq.a 
    LIBS += ../3rdparty/build/lib/libsodium.a 
    LIBS += -ldns_sd -lrt -ludev -lqjson 
}

macx {
    INCLUDEPATH += /usr/local/include 
    INCLUDEPATH += /usr/local/include/libusb-1.0 
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq.so
}

include (../3rdparty/nzmqt/nzmqt.pri)




