#include <QCoreApplication>
#include <QMetaObject>
#include <iostream>

#include "app_controller.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
        
    QSharedPointer<AppController> app_controller(new AppController);
    QMetaObject::invokeMethod(app_controller.data(), "init");
    return app.exec();
}
