QT += core
QT -= gui
QT += network
CONFIG += staticlib

TEMPLATE = lib
TARGET = core

INCLUDEPATH += $$PWD/.. ../service ../lib

unix:!macx {
    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0
    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev
}

macx {
    INCLUDEPATH += /usr/local/include /usr/local/include/libusb-1.0
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq 
}

HEADERS += \
    bonjour/bonjourrecord.h \
    bonjour/bonjourservicebrowser.h \
    bonjour/bonjourserviceresolver.h \
    bonjour/bonjourserviceregister.h \
    registeredtyperesolver.h \
    client_controller.h \
    message_bus.h

SOURCES += \
    bonjour/bonjourservicebrowser.cpp \
    bonjour/bonjourserviceresolver.cpp \
    bonjour/bonjourserviceregister.cpp \
    registeredtyperesolver.cpp \
    client_controller.cpp \
    message_bus.cpp

include (../3rdparty/nzmqt/nzmqt.pri)

