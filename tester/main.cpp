#include <QCoreApplication>
#include <QSharedPointer>

#include "client_controller.h"

using namespace nzmqt;

int main(int argc, char *argv[]) {
    qRegisterMetaType<ClientMessagingController::State>("ClientMessagingController::State");
    
    QCoreApplication app(argc, argv);
    
    int pub_port = -1;
    int msg_port = -1;
    
    for(int index = 0; index < argc; ++index) {
        QString arg = app.arguments().at(index);
        if(arg == "-pub_port")
            pub_port = app.arguments().at(index + 1).toInt();
        if(arg == "-msg_port")
            msg_port = app.arguments().at(index + 1).toInt();
    }
    
    QSharedPointer<ClientMessagingController> controller(new ClientMessagingController());   
    controller->init(pub_port, msg_port);
    
    return app.exec();
}

