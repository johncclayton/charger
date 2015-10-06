#include <QJsonDocument>
#include <QJsonObject>

#include "icharger/channel_status.h"
#include "icharger/icharger_message_keys.h"

ChannelStatus::ChannelStatus(QObject *parent) : QObject(parent) {
    
}

void ChannelStatus::setFromJson(QByteArray data) {
    int eChannel = channel();
    
    setObject( QJsonDocument::fromJson(data).object() );
    
    if(eChannel != channel())
        Q_EMIT onChannelChanged(channel());
}

quint8 ChannelStatus::channel() const {
    return object()[STR_CHANNEL_STATUS_CHANNEL_NUM].toInt();
}

void ChannelStatus::setChannel(quint8 i) {
    object()["channel"] = i;
}
 


