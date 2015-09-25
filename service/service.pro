
TEMPLATE = app
QT += network
QT -= gui

#CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES = \
    main.cpp \
    usb/icharger_usb.cpp \
#    bonjour/bonjourservicebrowser.cpp \
    bonjour/bonjourserviceregister.cpp \
#    bonjour/bonjourserviceresolver.cpp \
    zmq/zmq_publisher.cpp \
    usb/eventhandler.cpp \
    usb/hotplug_adapter.cpp \
    controller.cpp 

macx:INCLUDEPATH += /usr/local/include /usr/local/include/libusb-1.0
macx:LIBS += -L/usr/local/lib -lusb-1.0 -lzmq

HEADERS = \ 
    bonjour\bonjourrecord.h \
    usb/icharger_usb.h \
    usb/icharger_data.h \
    util/singleton.h \
    bonjour/bonjourrecord.h \
#    bonjour/bonjourservicebrowser.h \
    bonjour/bonjourserviceregister.h \
#    bonjour/bonjourserviceresolver.h \
    zmq/zmq_publisher.h \
    usb/eventhandler.h \
    usb/hotplug_adapter.h \
    controller.h 

TARGET = service

include (../3rdparty/nzmqt/nzmqt.pri)



