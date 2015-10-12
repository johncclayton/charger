#ifndef CHANNELSTATUS_H
#define CHANNELSTATUS_H

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>
#include <QVariantMap>
#include <QSharedPointer>

#include "cpp/cell_state.h"

class ChannelStatus : public QObject, private QJsonDocument
{
    Q_OBJECT
    Q_PROPERTY(quint8 channel READ channel NOTIFY channelChanged)
    Q_PROPERTY(quint32 outputPower READ outputPower NOTIFY outputPowerChanged)
    Q_PROPERTY(double outputCurrent READ outputCurrent NOTIFY outputCurrentChanged)
    Q_PROPERTY(double outputVoltage READ outputVoltage NOTIFY outputVoltageChanged)
    Q_PROPERTY(quint32 outputCapacity READ outputCapacity NOTIFY outputCapacityChanged)
    Q_PROPERTY(double inputVoltage READ inputVoltage NOTIFY inputVoltageChanged)
    Q_PROPERTY(double tempExternal READ tempExternal NOTIFY tempExternalChanged)
    Q_PROPERTY(double tempInternal READ tempInternal NOTIFY tempInternalChanged)
    Q_PROPERTY(double totalResistance READ totalResistance NOTIFY totalResistanceChanged)
    Q_PROPERTY(double lineInternalResistance READ lineInternalResistance NOTIFY lineInternalResistanceChanged)

    Q_PROPERTY(CellState* cell1 READ cell1 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell2 READ cell2 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell3 READ cell3 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell4 READ cell4 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell5 READ cell5 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell6 READ cell6 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell7 READ cell7 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell8 READ cell8 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell9 READ cell9 NOTIFY cellValuesChanged)
    Q_PROPERTY(CellState* cell10 READ cell10 NOTIFY cellValuesChanged)
    
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
    
    CellState* cell1() const;
    CellState* cell2() const;
    CellState* cell3() const;
    CellState* cell4() const;
    CellState* cell5() const;
    CellState* cell6() const;
    CellState* cell7() const;
    CellState* cell8() const;
    CellState* cell9() const;
    CellState* cell10() const;
    
    double totalResistance() const;
    double lineInternalResistance() const;
    quint8 cycleCount() const;
    quint32 controlStatus() const;
    quint32 runStatus() const;
    quint32 runError() const;
    quint32 dialogBoxId() const;
    
signals:
    void cellValuesChanged(int index);
    void channelChanged();
    void outputCurrentChanged();
    void outputVoltageChanged();
    void inputVoltageChanged();
    void outputCapacityChanged();
    void outputPowerChanged();
    void tempExternalChanged();
    void tempInternalChanged();
    void totalResistanceChanged();
    void lineInternalResistanceChanged();
    
public slots:
    void setFromJson(QByteArray data);
    
private:
    QVariantMap getCellData(int index);
    
    QList<CellStatePtr> _cells; // 10 is the max
};

typedef QSharedPointer<ChannelStatus> ChannelStatusPtr;

#endif // CHANNELSTATUS_H
