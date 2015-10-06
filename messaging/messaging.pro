QT += core
QT -= gui
QT += network
CONFIG += staticlib

TEMPLATE = lib
TARGET = messaging

INCLUDEPATH += $$PWD $$PWD/.. 

HEADERS += \
    icharger/icharger_message_keys.h \ 
    icharger/cell_state.h \
    icharger/channel_status.h \
    icharger/charger_state.h \
    icharger/device_info.h \
    json_helper.h

SOURCES += \
    icharger/icharger_message_keys.cpp \ 
    icharger/cell_state.cpp \
    icharger/channel_status.cpp \
    icharger/charger_state.cpp \
    icharger/device_info.cpp \
    json_helper.cpp

unix:!macx {
    INCLUDEPATH += /usr/include/qjson
}

