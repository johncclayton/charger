TEMPLATE = app

CONFIG += c++11
QT += qml quick widgets

SOURCES += \
    cpp/main.cpp \ 
    cpp/channel_status.cpp \
    cpp/channel_view_model.cpp \
    cpp/cell_state.cpp \
    cpp/device_info.cpp \
    cpp/device_model.cpp \
    cpp/system_storage.cpp \
    cpp/format.cpp

HEADERS += \
    cpp/channel_status.h \
    cpp/channel_view_model.h \
    cpp/cell_state.h \
    cpp/device_info.h \
    cpp/device_model.h \
    cpp/system_storage.h \ 
    cpp/format.h
    
RESOURCES += \
    qml.qrc \
    icharger/icharger.qrc

INCLUDEPATH += ../client
INCLUDEPATH += ../bonjour
INCLUDEPATH += ../messaging
LIBS += ../client/libclient.a
LIBS += ../messaging/libmessaging.a
LIBS += ../bonjour/libbonjour.a
TARGET = Charger

#unix:!macx {
#    INCLUDEPATH += ../3rdparty/build/include/libusb-1.0
#    LIBS += ../3rdparty/build/lib/libusb-1.0.a -L/usr/lib/arm-linux-gnueabihf -lzmq -ldns_sd -lrt -ludev
#    LIBS += -lqjson 
#}

ios {
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib -lzmq 
}

macx {
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib -lzmq 
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = 

# Default rules for deployment.
include(deployment.pri)


