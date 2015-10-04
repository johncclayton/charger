QT += core
QT -= gui
QT += network
CONFIG += staticlib

TEMPLATE = lib
TARGET = bonjour

INCLUDEPATH += $$PWD/.. 

unix:!macx {
    LIBS += -L/usr/lib/arm-linux-gnueabihf -ldns_sd -lrt -ludev
}

macx {
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq 
}

HEADERS += \
    singleton.h \
    bonjourrecord.h \
    bonjourservicebrowser.h \
    bonjourserviceresolver.h \
    bonjourserviceregister.h 

SOURCES += \
    bonjourservicebrowser.cpp \
    bonjourserviceresolver.cpp \
    bonjourserviceregister.cpp 


