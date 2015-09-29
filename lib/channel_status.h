#ifndef CHANNELSTATUS_H
#define CHANNELSTATUS_H

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>

class ChannelStatus : public QObject, private QJsonDocument
{
    Q_OBJECT
    Q_PROPERTY(quint8 channel READ channel WRITE setChannel NOTIFY onChannelChanged)
public:
    explicit ChannelStatus(QObject *parent = 0);
    
    quint8 channel() const;
    
    ChannelStatus& operator=(const ChannelStatus& other) {
        setChannel(other.channel());
        return *this;
    }
    
signals:
    void onChannelChanged(quint8 i);
    
public slots:
    void setFromJson(QByteArray data);
    
    void setChannel(quint8 i);
    
private:
};

#endif // CHANNELSTATUS_H
