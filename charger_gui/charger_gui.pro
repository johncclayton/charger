TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp 
RESOURCES += qml.qrc
INCLUDEPATH += ../lib
LIBS += ../lib/libcore.a

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = 

# Default rules for deployment.
include(deployment.pri)

