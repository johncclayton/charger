#include <QCoreApplication>
#include <QSharedPointer>
#include "client_controller.h"

using namespace nzmqt;

int main(int argc, char *argv[]) {
    qRegisterMetaType<ClientMessagingController::State>("ClientMessagingController::State");
    
    QCoreApplication app(argc, argv);
    QSharedPointer<ClientMessagingController> controller(new ClientMessagingController());   
    controller->init();
    return app.exec();
}

