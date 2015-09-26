
#include <QList>
#include <QStringList>

#include "message_handler.h"
#include "nzmqt/nzmqt.hpp"
using namespace nzmqt;

MessageHandler::MessageHandler(nzmqt::ZMQContext* ctx, QObject *owner) : SocketBase(ctx, ZMQSocket::TYP_ROUTER, owner)
{
    connect(_socket, SIGNAL(messageReceived(QList<QByteArray>)), this, SLOT(message_received(QList<QByteArray>)));
}

bool MessageHandler::bind() {
    _socket->bindTo("tcp://*:*");
    
    char temp[255];
    size_t value_len = 255;
    _socket->getOption(ZMQSocket::OPT_LAST_ENDPOINT, temp, &value_len);
    
    QStringList parts = QString::fromLatin1(temp).split(":");
    setPort(parts.last().toInt());
        
    return _port != 0;
}

void MessageHandler::message_received(QList<QByteArray> msg) {
    
}
