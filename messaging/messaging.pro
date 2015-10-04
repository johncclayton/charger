QT += core
QT -= gui
QT += network
CONFIG += staticlib

TEMPLATE = lib
TARGET = messaging

INCLUDEPATH += $$PWD $$PWD/.. 

HEADERS += \
    icharger_message_keys.h 

SOURCES += \
    icharger_message_keys.cpp 


