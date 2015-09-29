#include <QDebug>
#include "nzmqt/nzmqt.hpp"
#include "message_bus.h"

using namespace nzmqt;

MessageBus::MessageBus(ZMQSocket* sub, ZMQSocket* msg, QObject *parent) : QObject(parent)
{
    connect(msg, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(message(QList<QByteArray>)));
    
    connect(sub, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(notification(QList<QByteArray>)));
    
    qDebug() << "messaging is now active.";
}

MessageBus::~MessageBus() {
    qDebug() << "messaging is now destroyed.";
}

void MessageBus::message(QList<QByteArray> msg) {
    qDebug() << "message:";
    foreach(QByteArray a, msg) {
        qDebug() << a;
    }
}

void MessageBus::notification(QList<QByteArray> msg) {
    qDebug() << "notification:";
    foreach(QByteArray a, msg) {
        qDebug() << a;
    }
}
