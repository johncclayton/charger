#include <QDebug>
#include "nzmqt/nzmqt.hpp"
#include "message_bus.h"

using namespace nzmqt;

MessageBus::MessageBus(ZMQSocket* sub, ZMQSocket* msg, QObject *parent) : 
    QObject(parent), _pub(sub), _msg(msg)
{
    connect(msg, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(messageReceived(QList<QByteArray>)));
    
    connect(sub, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(notificationReceived(QList<QByteArray>)));
    
    qDebug() << "message bus layer is now active.";
}

MessageBus::~MessageBus() {
    qDebug() << "message bus layer has now been destroyed.";
}

void MessageBus::messageReceived(QList<QByteArray> msg) {
    qDebug() << "response received:" << msg;
}

void MessageBus::notificationReceived(QList<QByteArray> msg) {
    QString topic = QString::fromUtf8(msg.at(0));
    
    if(topic.startsWith("/icharger/channel/")) {
        QByteArray data = msg.at(1);
        ChannelStatus channel;
        channel.setFromJson(data);
        Q_EMIT channelStatusChanged(channel);
    } else if(topic.startsWith("/icharger/device")) {
        QByteArray data = msg.at(1);
        DeviceInfo info;
        info.setFromJson(data);
        Q_EMIT deviceInfoChanged(info);
    } else {
        Q_EMIT messageResponseReceived(topic, msg);
    }
}

bool MessageBus::asyncRequest(QString responseTopic, QString requestPayload) {
    QList<QByteArray> msg;
    msg << "charger_service";
    msg << responseTopic.toUtf8();
    msg << requestPayload.toUtf8();
    return _msg->sendMessage(msg);
}
