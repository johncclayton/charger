QT += core
QT -= gui
QT += network
CONFIG += staticlib

TEMPLATE = lib
TARGET = client

INCLUDEPATH += $$PWD $$PWD/.. ../service ../client

unix:!macx {
    LIBS += -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev
}

ios {
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib -lzmq 
}

macx {
    INCLUDEPATH += /usr/local/include 
    LIBS += -L/usr/local/lib -lzmq 
}

HEADERS += \
    client_controller.h \
    message_bus.h \ 
    registered_type_resolver.h

SOURCES += \
    client_controller.cpp \
    message_bus.cpp \ 
    registered_type_resolver.cpp

include (../3rdparty/nzmqt/nzmqt.pri)

