#include <QDebug>
#include <QJsonObject>
#include "device_info.h"
#include "icharger/icharger_message_keys.h"

DeviceInfo::DeviceInfo(QObject *parent) : QObject(parent) {    
}

void DeviceInfo::setFromJson(QByteArray data) {
    setObject( QJsonDocument::fromJson(data).object() );
}

QString DeviceInfo::imageSource() const {
    return _img_source;
}

void DeviceInfo::setChannel1FromJson(QByteArray data) {
    _channel[0] = ChannelStatusPtr(new ChannelStatus(this));
    _channel[0]->setFromJson(data);
    Q_EMIT channel1Changed();
}

void DeviceInfo::setChannel2FromJson(QByteArray data) {
    _channel[1] = ChannelStatusPtr(new ChannelStatus(this));
    _channel[1]->setFromJson(data);
    Q_EMIT channel2Changed();
}

void DeviceInfo::setImageSource(QString value) {
    _img_source = value;
    Q_EMIT imageSourceChanged();
}

QString DeviceInfo::serialNumber() const { 
    return object()[STR_DEVICE_ONLY_SERIAL_NUMBER].toString().trimmed(); 
}

quint8 DeviceInfo::ch1Status() const { 
    return object()[STR_DEVICE_ONLY_CH1_STATUS].toInt() & 0x00ff; 
}

quint8 DeviceInfo::ch2Status() const { 
    return object()[STR_DEVICE_ONLY_CH2_STATUS].toInt() & 0x00ff; 
}

float DeviceInfo::softwareVersion() const { 
    return object()[STR_DEVICE_ONLY_SW_VERSION].toDouble(); 
}

float DeviceInfo::hardwareVersion() const { 
    return object()[STR_DEVICE_ONLY_HW_VERSION].toDouble(); 
}

QString DeviceInfo::manufacturer() const {
    return object()[STR_DEVICE_ONLY_MANUFACTURER].toString();
}

QString DeviceInfo::product() const {
    return object()[STR_DEVICE_ONLY_PRODUCT].toString();    
}

