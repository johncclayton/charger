QT += core
QT -= gui
QT += network
CONFIG += staticlib

TEMPLATE = lib
TARGET = messaging

INCLUDEPATH += $$PWD $$PWD/.. 

HEADERS += \
    json_helper.h \
    icharger_message_keys.h 

SOURCES += \
    json_helper.cpp \
    icharger_message_keys.cpp 


