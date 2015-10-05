#include <QDebug>

#include "nzmqt/nzmqt.hpp"
#include "message_bus.h"
#include "messaging/json_helper.h"

using namespace nzmqt;

#define SECONDS_5_MS (1000 * 5)

MessageBus::MessageBus(QObject *parent) : 
    QObject(parent), _pub(0), _msg(0), _alive(false)
{
    _lastHeartbeat = QDateTime::currentDateTime();
    startTimer(1000);    
}

MessageBus::~MessageBus() {
}

void MessageBus::setPublishSocket(ZMQSocket* s) {
    if(_pub)
        disconnect(_pub);
    
    _pub = s;

    if(_pub)
        connect(_pub, SIGNAL(messageReceived(QList<QByteArray>)), 
                this, SLOT(processNotification(QList<QByteArray>)));
}

void MessageBus::setMessageSocket(ZMQSocket* s) {
    if(_msg)
        disconnect(_msg);
    
    _msg = s;
    
    if(_msg)
        connect(_msg, SIGNAL(messageReceived(QList<QByteArray>)), 
                this, SLOT(processMessageResponse(QList<QByteArray>)));
}

void MessageBus::getDevices() const {
    syncRequest("get-devices");    
}

void MessageBus::getDeviceInformation(QString key) const {
    QList<QByteArray> req;
    req << "get-device";
    req << key.toUtf8();
    syncRequest(req);
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
        // key and added fields.. then go get the initial snapshot and topics
        QVariantMap data = jsonToVariantMap(msg.at(1));
        Q_EMIT deviceAddedRemoved(data["added"].toBool(), data["key"].toString());
    }
    
    Q_EMIT notificationReceived(topic, msg.mid(1));
}

bool MessageBus::syncRequest(QList<QByteArray> requestPayload) const {   
    requestPayload.prepend(QByteArray());
    return _msg->sendMessage(requestPayload);
}

bool MessageBus::syncRequest(QByteArray requestPayload) const {   
    QList<QByteArray> msg;
    msg << requestPayload;
    return syncRequest(msg);
}
