QT += core
QT -= gui
QT += network

TEMPLATE = app
TARGET = tester
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += ../lib ../service
LIBS += ../lib/libcore.a

unix:!macx {
#    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0
    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev
}

macx {
#    INCLUDEPATH += /usr/local/include /usr/local/include/libusb-1.0
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq 
}

SOURCES += main.cpp 

