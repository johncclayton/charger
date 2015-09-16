QT += testlib
QT -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
DEPENDPATH += . TestChargerUSB
INCLUDEPATH += ../core . TestChargerUSB

#QMAKE_LIBDIR += /usr/lib/arm-linux-gnueabihf
LIBS += /usr/lib/arm-linux-gnueabihf/libusb-1.0.so ../build/lib/libcharger_core.so

DESTDIR = ../build/bin

# Input
HEADERS += TestChargerUSB/TestChargerUSB.h
SOURCES += main.cpp TestChargerUSB/TestChargerUSB.cpp
