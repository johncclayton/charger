#include <QCoreApplication>
#include <iostream>

#include "controller.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    
    Controller main_controller;
    int r = main_controller.init();
    if(r == 0)
        return app.exec();
    
    std::cerr << "failure to initialise" << std::endl;
    
    return r;
}
