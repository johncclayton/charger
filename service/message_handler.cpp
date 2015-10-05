
#include <QList>
#include <QStringList>
#include <QDebug>

#include "message_handler.h"
#include "nzmqt/nzmqt.hpp"

using namespace nzmqt;

MessageHandler::MessageHandler(nzmqt::ZMQContext* ctx, QObject *owner) : 
    SocketBase(ctx, ZMQSocket::TYP_ROUTER, owner)
{
    _socket->setIdentity("charger_service");
    connect(_socket, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(message_received(QList<QByteArray>)));
}

bool MessageHandler::bind(int port) {
    QString port_value("*");
    if(port != 0)
        port_value = QString::number(port);
    _socket->bindTo(QString("tcp://*:%1").arg(port_value));
    
    char temp[255];
    size_t value_len = 255;
    _socket->getOption(ZMQSocket::OPT_LAST_ENDPOINT, temp, &value_len);
    
    QStringList parts = QString::fromLatin1(temp).split(":");
    setPort(parts.last().toInt());
    
    return _port != 0;
}

void MessageHandler::message_received(QList<QByteArray> msg) {
    QList<QByteArray> return_path;

    int index = 0;
    while(!msg.at(index).isEmpty() && index < msg.size()) {
        return_path << msg.at(index);
        ++index;
    }
    
    QList<QByteArray> payload(msg.mid(index + 1));
    
    Q_EMIT handle_message(return_path, payload);
}

void MessageHandler::send_response(QList<QByteArray> return_path, QList<QByteArray> payload) {
    QList<QByteArray> msg;
    msg << return_path;
    msg << QByteArray();
    msg << payload;
    _socket->sendMessage(msg);
}

void MessageHandler::send_response(QList<QByteArray> return_path, QByteArray payload) {
    QList<QByteArray> msg;
    msg << payload;
    send_response(return_path, msg);
}
