#ifndef CHARGER_STATE_H
#define CHARGER_STATE_H

#include <QObject>
#include "channel_status.h"

class ChargerState : public QObject
{
    Q_OBJECT
public:
    
    Q_PROPERTY(ChannelStatus ch1 READ ch1 WRITE setCh1 NOTIFY onCh1Changed)
    Q_PROPERTY(ChannelStatus ch2 READ ch2 WRITE setCh2 NOTIFY onCh2Changed)
    
    explicit ChargerState(QObject *parent = 0);
    
    const ChannelStatus& ch1() const { return _ch1; }
    const ChannelStatus& ch2() const { return _ch2; }
    
signals:
    void onCh1Changed(const ChannelStatus& ch);
    void onCh2Changed(const ChannelStatus& ch);
    
public slots:
    void setCh1(const ChannelStatus& ch) { _ch1 = ch; Q_EMIT onCh1Changed(ch); }
    void setCh2(const ChannelStatus& ch) { _ch2 = ch; Q_EMIT onCh2Changed(ch); }
    
private:
    ChannelStatus _ch1;
    ChannelStatus _ch2;    
};

#endif // CHARGER_STATE_H
