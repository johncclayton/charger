#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>

/*
 * struct device_only {
    register16   device_id;
    s8           device_sn[12];
    register16   sw_version;
    register16   hw_version;
    register16   system_length;
    register16   memory_length;
    register16   ch1_status;
    register16   ch2_status;
} __attribute__ ((packed));
*/

class DeviceInfo : public QObject, private QJsonDocument
{
    Q_OBJECT
public:
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY onSerialNumberChanged)
    Q_PROPERTY(float softwareVersion READ softwareVersion NOTIFY onSoftwareVersionChanged)
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
    
    DeviceInfo& operator=(const DeviceInfo& other) {
        setSerialNumber(other.serialNumber());
        setSoftwareVersion(other.softwareVersion());
        setCh1Status(other.ch1Status());
        setCh2Status(other.ch2Status());
        return *this;
    }

    QString serialNumber() const;
    float softwareVersion() const;
    quint8 ch1Status() const;
    quint8 ch2Status() const;
    
    Q_ENUMS(Status)
    
signals:
    void onSerialNumberChanged();
    void onSoftwareVersionChanged();
    void onCh1StatusChanged();
    void onCh2StatusChanged();
    
public slots:
    void setFromJson(QByteArray data);
    
    void setSerialNumber(QString value);
    void setSoftwareVersion(float value);
    void setCh1Status(quint8 value);
    void setCh2Status(quint8 value);
};

#endif // DEVICEINFO_H
