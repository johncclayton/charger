#ifndef CHANNELSTATUS_H
#define CHANNELSTATUS_H

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>
#include <QSharedPointer>

class ChannelStatus : public QObject, private QJsonDocument
{
    Q_OBJECT
    Q_PROPERTY(quint8 channel READ channel NOTIFY channelChanged)
    Q_PROPERTY(quint32 outputPower READ outputPower)
    Q_PROPERTY(double outputCurrent READ outputCurrent)
    Q_PROPERTY(double outputVoltage READ outputVoltage)
    Q_PROPERTY(quint32 outputCapacity READ outputCapacity)
    Q_PROPERTY(double inputVoltage READ inputVoltage)
    Q_PROPERTY(double tempExternal READ tempExternal)
    Q_PROPERTY(double tempInternal READ tempInternal)
    Q_PROPERTY(double totalResistance READ totalResistance)
    Q_PROPERTY(double lineInternalResistance READ lineInternalResistance)
    Q_PROPERTY(quint8 cycleCount READ cycleCount)
    Q_PROPERTY(quint32 controlStatus READ controlStatus)
    Q_PROPERTY(quint32 runStatus READ runStatus)
    Q_PROPERTY(quint32 runError READ runError)
    Q_PROPERTY(quint32 dialogBoxId READ dialogBoxId)
    
public:
    explicit ChannelStatus(QObject *parent = 0);
    
    quint8 channel() const;
    quint32 outputPower() const;
    double outputCurrent() const;
    double outputVoltage() const;
    quint32 outputCapacity() const;
    
    double inputVoltage() const;
    double tempExternal() const;
    double tempInternal() const;
    
    double totalResistance() const;
    double lineInternalResistance() const;
    quint8 cycleCount() const;
    quint32 controlStatus() const;
    quint32 runStatus() const;
    quint32 runError() const;
    quint32 dialogBoxId() const;
    
signals:
    void channelChanged(quint8 i);
    
public slots:
    void setFromJson(QByteArray data);
};

typedef QSharedPointer<ChannelStatus> ChannelStatusPtr;

#endif // CHANNELSTATUS_H
