#include "message.h"

using namespace nzmqt;

Message::Message(ZMQSocket* msg, ZMQSocket* sub, QObject *parent) : QObject(parent)
{
    _message = msg;
    _subscribe = sub;
    
    connect(_message, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(message(QList<QByteArray>)));
    
    connect(_subscribe, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(notification(QList<QByteArray>)));
}

void Message::message(QList<QByteArray> msg) {
    
}

void Message::notification(QList<QByteArray> msg) {
    
}
