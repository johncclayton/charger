#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>

#include "cpp/channel_status.h"

class DeviceInfo : public QObject, private QJsonDocument
{
    Q_OBJECT
public:
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(QString manufacturer READ manufacturer NOTIFY manufacturerChanged)
    Q_PROPERTY(QString product READ product NOTIFY productChanged)
    Q_PROPERTY(float softwareVersion READ softwareVersion NOTIFY softwareVersionChanged)
    Q_PROPERTY(float hardwareVersion READ hardwareVersion NOTIFY hardwareVersionChanged)
    Q_PROPERTY(quint8 ch1Status READ ch1Status NOTIFY ch1StatusChanged)
    Q_PROPERTY(quint8 ch2Status READ ch2Status NOTIFY ch2StatusChanged)
    
    Q_PROPERTY(ChannelStatus* ch1 READ channel1 NOTIFY channel1Changed)
    Q_PROPERTY(ChannelStatus* ch2 READ channel2 NOTIFY channel2Changed)
    
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    
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
        
    QString key() const { return _key; }
    void setKey(QString key) { _key = key; }
    
    QString serialNumber() const;
    QString imageSource() const;
    QString manufacturer() const;
    QString product() const;
    float softwareVersion() const;
    float hardwareVersion() const;
    quint8 ch1Status() const;
    quint8 ch2Status() const;
    
    ChannelStatus* channel1() const { return _channel[0].data(); }
    ChannelStatus* channel2() const { return _channel[1].data(); }
    bool running() const;
    
    Q_ENUMS(Status)
    
signals:
    void runningChanged();
    void imageSourceChanged();
    void serialNumberChanged();
    void softwareVersionChanged();
    void hardwareVersionChanged();
    void productChanged();
    void manufacturerChanged();
    void ch1StatusChanged();
    void ch2StatusChanged();
    
    void channel1Changed();
    void channel2Changed();
    
public slots:
    void setFromJson(QByteArray data);
    void setChannel1FromJson(QByteArray data);
    void setChannel2FromJson(QByteArray data);
    void setImageSource(QString value);
    
private:
    QString _key;
    QString _img_source;  
    ChannelStatusPtr _channel[2];
};

#endif // DEVICEINFO_H
