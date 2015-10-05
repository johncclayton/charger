
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
    while(!msg.at(index).isNull()) {
        return_path.append(msg.at(index));
        ++index;
    }
    
    QList<QByteArray> payload;
    payload.append(msg.mid(index));

    qDebug() << "return path:" << return_path;
    qDebug() << "payload" << payload;    
}
