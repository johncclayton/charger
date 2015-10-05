TEMPLATE = app

CONFIG += c++11
QT += qml quick widgets

SOURCES += main.cpp \ 
    qjsonitem.cpp \
    qjsonmodel.cpp \
    device_model.cpp

HEADERS += \
    qjsonitem.h \
    qjsonmodel.h \
    device_model.h

RESOURCES += qml.qrc
INCLUDEPATH += ../client
INCLUDEPATH += ../bonjour
INCLUDEPATH += ../messaging
LIBS += ../client/libclient.a
LIBS += ../messaging/libmessaging.a
LIBS += ../bonjour/libbonjour.a
TARGET = Charger

unix:!macx {
    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0
    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev
    LIBS += -lqjson 
}

macx {
    INCLUDEPATH += /usr/local/include /usr/local/include/libusb-1.0
    LIBS += -L/usr/local/lib -lusb-1.0 -lzmq 
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = 

# Default rules for deployment.
include(deployment.pri)


