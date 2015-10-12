#include <QCoreApplication>
#include <QMetaObject>
#include <iostream>

#include "app_controller.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Q_ASSERT( sizeof(register16) == 2 );
    Q_ASSERT( sizeof(register32) == 4 );
    Q_ASSERT( sizeof(device_only) == 26 );

    int pub_port = 0;
    int msg_port = 0;
    bool test = false;
    
    for(int index = 0; index < argc; ++index) {
        QString arg = app.arguments().at(index);
        if(arg == "-pub_port")
            pub_port = app.arguments().at(index + 1).toInt();
        if(arg == "-msg_port")
            msg_port = app.arguments().at(index + 1).toInt();
        if(arg == "-test")
            test = true;
    }
        
    AppController app_controller;
    if(0 == app_controller.init(pub_port, msg_port)) {
        return app.exec();
    }
    
    std::cerr << "unable to init program";
    
    return -1;
}
