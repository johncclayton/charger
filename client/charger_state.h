#ifndef CHARGER_STATE_H
#define CHARGER_STATE_H

#include <QObject>
#include "channel_status.h"
#include "device_info.h"

class ChargerState : public QObject
{
    Q_OBJECT
    
public:
    Q_PROPERTY(DeviceInfo info READ info NOTIFY infoChanged)
    Q_PROPERTY(ChannelStatus ch1 READ ch1 NOTIFY ch1Changed)
    Q_PROPERTY(ChannelStatus ch2 READ ch2 NOTIFY ch2Changed)
    
    explicit ChargerState(QObject *parent = 0);
    
    const DeviceInfo& info() const { return _info; }
    const ChannelStatus& ch1() const { return _ch1; }
    const ChannelStatus& ch2() const { return _ch2; }
    
signals:
    void infoChanged();
    void ch1Changed();
    void ch2Changed();
    
public slots:
    void setDeviceInfo(const DeviceInfo& info) { _info = info; Q_EMIT infoChanged(); }
    void setCh1(const ChannelStatus& ch) { _ch1 = ch; Q_EMIT ch1Changed(); }
    void setCh2(const ChannelStatus& ch) { _ch2 = ch; Q_EMIT ch2Changed(); }
    
private:
    DeviceInfo _info;
    ChannelStatus _ch1;
    ChannelStatus _ch2;    
};

#endif // CHARGER_STATE_H
