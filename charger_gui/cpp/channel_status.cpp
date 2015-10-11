#include <QJsonDocument>
#include <QJsonObject>

#include "cpp/channel_status.h"
#include "icharger/icharger_message_keys.h"

ChannelStatus::ChannelStatus(QObject *parent) : QObject(parent) {    
}

void ChannelStatus::setFromJson(QByteArray data) {
    int eChannel = channel();
    
    setObject( QJsonDocument::fromJson(data).object() );
    
    if(eChannel != channel())
        Q_EMIT channelChanged(channel());
}

quint8 ChannelStatus::channel() const {
    return object()[STR_CHANNEL_STATUS_CHANNEL_NUM].toInt();
}

quint32 ChannelStatus::outputPower() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_POWER].toInt();    
}

double ChannelStatus::outputCurrent() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_CURRENT].toDouble();    
}

double ChannelStatus::outputVoltage() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_VOLTAGE].toDouble();    
}

quint32 ChannelStatus::outputCapacity() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_CAPACITY].toInt();    
}

double ChannelStatus::inputVoltage() const {
    return object()[STR_CHANNEL_STATUS_INPUT_VOLTAGE].toDouble();    
}

double ChannelStatus::tempExternal() const {
    return object()[STR_CHANNEL_STATUS_TEMP_EXTERNAL].toDouble();    
}

double ChannelStatus::tempInternal() const {
    return object()[STR_CHANNEL_STATUS_TEMP_INTERNAL].toDouble();    
}

double ChannelStatus::totalResistance() const {
    return object()[STR_CHANNEL_STATUS_TOTAL_RESISTANCE].toDouble();    
}

double ChannelStatus::lineInternalResistance() const {
    return object()[STR_CHANNEL_STATUS_LINE_INTERNAL_RESISTANCE].toDouble();    
}

quint8 ChannelStatus::cycleCount() const {
    return object()[STR_CHANNEL_STATUS_CYCLE_COUNT].toInt();    
}

quint32 ChannelStatus::controlStatus() const {
    return object()[STR_CHANNEL_STATUS_CONTROL_STATUS].toInt();    
}

quint32 ChannelStatus::runStatus() const {
    return object()[STR_CHANNEL_STATUS_RUN_STATUS].toInt();    
}

quint32 ChannelStatus::runError() const {
    return object()[STR_CHANNEL_STATUS_RUN_ERROR].toInt();
}

quint32 ChannelStatus::dialogBoxId() const {
    return object()[STR_CHANNEL_STATUS_DIALOG_BOX_ID].toInt();    
}




