#include <QCoreApplication>
#include <QSharedPointer>
#include "testcontroller.h"

using namespace nzmqt;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QSharedPointer<TestController> controller(new TestController());   
    controller->init();
    return app.exec();
}

