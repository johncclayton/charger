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
    Q_UNUSED(msg);
}

void MessageBus::notification(QList<QByteArray> msg) {
    QString topic = QString::fromUtf8(msg.at(0));
    
    if(topic.startsWith("/icharger/channel/")) {
        QByteArray data = msg.at(1);
        ChannelStatus channel;
        channel.setFromJson(data);
        Q_EMIT channelStatusUpdated(channel);
    } else if(topic.startsWith("/icharger/device")) {
        QByteArray data = msg.at(1);
        DeviceInfo info;
        info.setFromJson(data);
        Q_EMIT deviceInfoUpdated(info);
    }
}
