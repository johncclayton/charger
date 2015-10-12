#include <QByteArray>
#include <QJsonObject>
#include <QDebug> 

#include "cpp/cell_state.h"
#include "icharger/icharger_message_keys.h"

CellState::CellState(QObject *parent) : QObject(parent) {    
}

void CellState::setFromJson(QByteArray data) {
    double oldValue = cellVoltage();
    double oldR = cellResistance();
    QString oldUnits = cellUnits();
    
    setObject( QJsonDocument::fromJson(data).object() );    
    
    if(oldValue != cellVoltage())
        Q_EMIT voltageChanged();
    if(oldR != cellResistance())
        Q_EMIT resistanceChanged();
    if(oldUnits != cellUnits())
        Q_EMIT unitsChanged();
}

double CellState::cellVoltage() const {
    return object()[STR_CHANNEL_STATUS_CELL_VOLTAGE].toDouble(); 
}

double CellState::cellResistance() const {
    return object()[STR_CHANNEL_STATUS_CELL_RESISTANCE].toDouble(); 
}

QString CellState::cellUnits() const {
    return _units;
}

bool CellState::differsFrom(const CellState& other) const {
    return  cellVoltage() != other.cellVoltage() ||
            cellResistance() != other.cellResistance() ||
            cellUnits() != other.cellUnits();
}


