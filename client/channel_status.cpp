#include <QJsonDocument>
#include <QJsonObject>

#include "channel_status.h"

ChannelStatus::ChannelStatus(QObject *parent) : QObject(parent) {
    
}

void ChannelStatus::setFromJson(QByteArray data) {
    int eChannel = channel();
    
    setObject( QJsonDocument::fromJson(data).object() );
    
    if(eChannel != channel())
        Q_EMIT onChannelChanged(channel());
}

quint8 ChannelStatus::channel() const {
    return object()["channel"].toInt();
}

void ChannelStatus::setChannel(quint8 i) {
    object()["channel"] = i;
}
 


