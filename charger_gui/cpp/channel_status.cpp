#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "cpp/channel_status.h"
#include "icharger/icharger_message_keys.h"
#include "json_helper.h"

ChannelStatus::ChannelStatus(QObject *parent) : QObject(parent) {    
    for(int index = 0; index < 10; ++index) {
        _cells.push_back(CellStatePtr(new CellState(this)));
    }
}

void ChannelStatus::setFromJson(QByteArray data) {
    int eChannel = channel();
    double eOutputPower = outputPower();
    double eOutputCurrent = outputCurrent();
    double eOutputVoltage = outputVoltage();
    double eOutputCapacity = outputCapacity();
    double eInputVoltage = inputVoltage();
    double eTempExternal = tempExternal();
    double eTempInternal = tempInternal();
    double eTotalResistance = totalResistance();
    double eLineInternalResistance = lineInternalResistance();
    
    setObject( QJsonDocument::fromJson(data).object() );

    QVariantList cell_data = object().value("cells").toArray().toVariantList();
    
    if(!cell_data.isEmpty()) {
        QList<CellStatePtr> old(_cells);
        
        // remove all cell states, re-pop
        _cells.clear();
        
        for(int index = 0; index < 10; ++index) {
            CellStatePtr newCell(CellStatePtr(new CellState(this)));
            _cells.push_back(newCell);
            QVariantMap data = cell_data.at(index).toMap();
            newCell->setFromJson(variantMapToJson(data));            
                
            if(old.size() > index) {
                CellStatePtr oldState(old.at(index));
                if(oldState->differsFrom(*newCell))
                    Q_EMIT cellValuesChanged(index);
            } else {
                Q_EMIT cellValuesChanged(index);
            }
        }
    }
    
    if(eChannel != channel())
        Q_EMIT channelChanged();
    if(eOutputPower !=  outputPower())
        Q_EMIT outputPowerChanged();
    if(eOutputCurrent != outputCurrent())
        Q_EMIT outputCurrentChanged();
    if(eOutputVoltage != outputVoltage())
        Q_EMIT outputVoltageChanged();
    if(eOutputCapacity != outputCapacity())
        Q_EMIT outputCapacity();
    if(eInputVoltage != inputVoltage())
        Q_EMIT inputVoltageChanged();
    if(eTempExternal != tempExternal())
        Q_EMIT tempExternalChanged();
    if(eTempInternal != tempInternal())
        Q_EMIT tempInternalChanged();
    if(eTotalResistance != totalResistance())
        Q_EMIT totalResistanceChanged();
    if(eLineInternalResistance != lineInternalResistance())
        Q_EMIT lineInternalResistanceChanged();
}

CellState* ChannelStatus::findCellNumber(int num) const {
    CellStatePtr s = _cells.at(num);
    if(s->number() == num)
        return s.data();
    for(int i = 0; i < 10; ++i) {
        if(_cells.at(i)->number() == num)
            return _cells.at(i).data();
    }
    
    Q_ASSERT(false);
}

CellState* ChannelStatus::cell1() const {
    return findCellNumber(0);
}

CellState* ChannelStatus::cell2() const {
    return findCellNumber(1);
}

CellState* ChannelStatus::cell3() const {
    return findCellNumber(2);
}

CellState* ChannelStatus::cell4() const {
    return findCellNumber(3);
}

CellState* ChannelStatus::cell5() const {
    return findCellNumber(4);
}

CellState* ChannelStatus::cell6() const {
    return findCellNumber(5);
}

CellState* ChannelStatus::cell7() const {
    return findCellNumber(6);
}

CellState* ChannelStatus::cell8() const {
    return findCellNumber(7);
}

CellState* ChannelStatus::cell9() const {
    return findCellNumber(8);
}

CellState* ChannelStatus::cell10() const {
    return findCellNumber(9);
}

quint8 ChannelStatus::channel() const {
    return object()[STR_CHANNEL_STATUS_CHANNEL_NUM].toInt();
}

quint32 ChannelStatus::outputPower() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_POWER].toInt();    
}

double ChannelStatus::outputCurrent() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_CURRENT].toDouble();    
}

double ChannelStatus::outputVoltage() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_VOLTAGE].toDouble();    
}

quint32 ChannelStatus::outputCapacity() const {
    return object()[STR_CHANNEL_STATUS_OUTPUT_CAPACITY].toInt();    
}

double ChannelStatus::inputVoltage() const {
    return object()[STR_CHANNEL_STATUS_INPUT_VOLTAGE].toDouble();    
}

double ChannelStatus::tempExternal() const {
    return object()[STR_CHANNEL_STATUS_TEMP_EXTERNAL].toDouble();    
}

double ChannelStatus::tempInternal() const {
    return object()[STR_CHANNEL_STATUS_TEMP_INTERNAL].toDouble();    
}

double ChannelStatus::totalResistance() const {
    return object()[STR_CHANNEL_STATUS_TOTAL_RESISTANCE].toDouble();    
}

double ChannelStatus::lineInternalResistance() const {
    return object()[STR_CHANNEL_STATUS_LINE_INTERNAL_RESISTANCE].toDouble();    
}

quint8 ChannelStatus::cycleCount() const {
    return object()[STR_CHANNEL_STATUS_CYCLE_COUNT].toInt();    
}

quint32 ChannelStatus::controlStatus() const {
    return object()[STR_CHANNEL_STATUS_CONTROL_STATUS].toInt();    
}

quint32 ChannelStatus::runStatus() const {
    return object()[STR_CHANNEL_STATUS_RUN_STATUS].toInt();    
}

quint32 ChannelStatus::runError() const {
    return object()[STR_CHANNEL_STATUS_RUN_ERROR].toInt();
}

quint32 ChannelStatus::dialogBoxId() const {
    return object()[STR_CHANNEL_STATUS_DIALOG_BOX_ID].toInt();    
}




