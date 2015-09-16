TEMPLATE = lib

SOURCES += icharger.cpp 
HEADERS += icharger.h

DESTDIR = ../build/lib
DEFINES += CORE_LIBRARY
TARGET = charger_core

INCLUDEPATH += /usr/include/libusb-1.0
