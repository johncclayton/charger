#include <QCoreApplication>
#include "message.h"

using namespace nzmqt;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    ZMQContext* ctx = createDefaultContext();
    ZMQSocket* message = ctx->createSocket(ZMQSocket::TYP_DEALER);
    ZMQSocket* subscribe = ctx->createSocket(ZMQSocket::TYP_SUB);

    message->connectTo("tcp://192.168.178.101:");
    subscribe->connectTo("tcp://192.168.178.101:");
        
    Message testing(message, subscribe);

    int r = app.exec();
    
    delete subscribe;
    delete message;
    delete ctx;
    
    return r;
}

