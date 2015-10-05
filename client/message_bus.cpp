#include <QDebug>

#include "nzmqt/nzmqt.hpp"
#include "message_bus.h"
#include "messaging/json_helper.h"

using namespace nzmqt;

#define SECONDS_5_MS (1000 * 5)

MessageBus::MessageBus(ZMQSocket* sub, ZMQSocket* msg, QObject *parent) : 
    QObject(parent), _pub(sub), _msg(msg), _alive(false)
{
    connect(msg, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(processMessageResponse(QList<QByteArray>)));
    
    connect(sub, SIGNAL(messageReceived(QList<QByteArray>)), 
            this, SLOT(processNotification(QList<QByteArray>)));

    _lastHeartbeat = QDateTime::currentDateTime();
    startTimer(1000);
    
    qDebug() << "message bus layer is now active.";
}

MessageBus::~MessageBus() {
    qDebug() << "message bus layer has now been destroyed.";
}

void MessageBus::setAlive(bool value) {
    if(value != _alive) {
        _alive = value;
        Q_EMIT aliveChanged();
        qDebug() << "alive:" << _alive;
    }
}

void MessageBus::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);
    // if we get to 5 seconds without a heartbeat... ISSUES!
    QDateTime n = QDateTime::currentDateTime();
    double diff = n.toMSecsSinceEpoch() - _lastHeartbeat.toMSecsSinceEpoch();
    if(diff > SECONDS_5_MS) {
        setAlive(false);
    } else {
        setAlive(true);
    }
}

void MessageBus::processMessageResponse(QList<QByteArray> msg) {
    if(msg.size() > 1)
        qDebug() << "response received:" << msg.mid(1);
}

void MessageBus::processNotification(QList<QByteArray> msg) {
    QString topic = QString::fromUtf8(msg.at(0));
    if(topic == "/heartbeat") {
        _lastHeartbeat = QDateTime::currentDateTime();
        Q_EMIT heartbeat();
    } else if(topic == "/device") {
        QByteArray deviceJson = msg.at(1);        
    }
    
    Q_EMIT notificationReceived(topic, msg.mid(1));
}

bool MessageBus::asyncRequest(QString requestPayload) {   
    QList<QByteArray> msg;
    msg << QByteArray();
    msg << requestPayload.toUtf8();
    return _msg->sendMessage(msg);
}
