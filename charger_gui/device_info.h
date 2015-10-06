#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>

class DeviceInfo : public QObject, private QJsonDocument
{
    Q_OBJECT
public:
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY onSerialNumberChanged)
    Q_PROPERTY(QString imageSource READ imageSource NOTIFY onImageSourceChanged)
    Q_PROPERTY(float softwareVersion READ softwareVersion NOTIFY onSoftwareVersionChanged)
    Q_PROPERTY(float hardwareVersion READ hardwareVersion NOTIFY onHardwareVersionChanged)
    Q_PROPERTY(quint8 ch1Status READ ch1Status NOTIFY onCh1StatusChanged)
    Q_PROPERTY(quint8 ch2Status READ ch2Status NOTIFY onCh2StatusChanged)
    
    explicit DeviceInfo(QObject *parent = 0);
    
    enum StatusBits {
        RUN         = 0x01,
        ERROR       = 0x02,
        CONTROL     = 0x04,
        RUN_STATUS  = 0x08,
        DLG_STATUS  = 0x10,
        CELL_VOLT   = 0x20,
        BALANCE     = 0x40
    };
        
    QString serialNumber() const;
    QString imageSource() const;
    float softwareVersion() const;
    float hardwareVersion() const;
    quint8 ch1Status() const;
    quint8 ch2Status() const;
    
    Q_ENUMS(Status)
    
signals:
    void onImageSourceChanged();
    void onSerialNumberChanged();
    void onSoftwareVersionChanged();
    void onHardwareVersionChanged();
    void onCh1StatusChanged();
    void onCh2StatusChanged();
    
public slots:
    void setFromJson(QByteArray data);
    
    void setImageSource(QString value);
    void setSerialNumber(QString value);
    void setSoftwareVersion(float value);
    void setHardwareVersion(float value);
    void setCh1Status(quint8 value);
    void setCh2Status(quint8 value);
};

#endif // DEVICEINFO_H
