#include <QCoreApplication>
#include <QMetaObject>
#include <iostream>

#include "app_controller.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
        
    AppController app_controller;
    if(0 == app_controller.init())
        return app.exec();
    
    std::cerr << "unable to init program";
    
    return -1;
}
