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
    QString v = object()["img_source"].toString();
    qDebug() << "image will be:" << v;
    return v;
}

void DeviceInfo::setImageSource(QString value) {
    object()["img_source"] = value;
    Q_EMIT onImageSourceChanged();
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

/*void DeviceInfo::setSerialNumber(QString value) {
    object()[STR_DEVICE_ONLY_SERIAL_NUMBER] = value;
}

void DeviceInfo::setSoftwareVersion(float value) {
    object()[STR_DEVICE_ONLY_SW_VERSION] = value;
}

void DeviceInfo::setHardwareVersion(float value) {
    object()[STR_DEVICE_ONLY_HW_VERSION] = value;
}

void DeviceInfo::setCh1Status(quint8 value) {
    object()[STR_DEVICE_ONLY_CH1_STATUS] = value;
}

void DeviceInfo::setCh2Status(quint8 value) {
    object()[STR_DEVICE_ONLY_CH2_STATUS] = value;
}*/
