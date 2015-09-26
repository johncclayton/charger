#include <QCoreApplication>
#include <iostream>

#include "app_controller.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    
    AppController app_controller;
    int r = app_controller.init();
    if(r == 0)
        return app.exec();
    
    std::cerr << "failure to initialise" << std::endl;
    
    return r;
}
