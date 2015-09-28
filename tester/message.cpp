#include <QDebug>
#include "message.h"

using namespace nzmqt;

Message::Message(ZMQSocket* sub, ZMQSocket* msg, QObject *parent) : QObject(parent)
{
    connect(msg, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(message(QList<QByteArray>)));
    
    connect(sub, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(notification(QList<QByteArray>)));
    
    qDebug() << "messaging is now active.";
}

Message::~Message() {
    qDebug() << "messaging is now destroyed.";
}

void Message::message(QList<QByteArray> msg) {
    foreach(QByteArray a, msg) {
        qDebug() << "message received:" << a;
    }
}

void Message::notification(QList<QByteArray> msg) {
    foreach(QByteArray a, msg) {
        qDebug() << "notification received:" << a;
    }
}
