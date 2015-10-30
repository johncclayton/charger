#include <QByteArray>
#include <QJsonObject>
#include <QDebug> 

#include "cpp/cell_state.h"
#include "icharger/icharger_message_keys.h"

CellState::CellState(QObject *parent) : QObject(parent) {    
}

void CellState::setFromJson(QByteArray data) {
    QString oldValue = voltage();
    double oldR = resistance();
    int eNum = number();
    QString oldUnits = units();
    
    setObject( QJsonDocument::fromJson(data).object() );    
    
    if(oldValue != voltage())
        Q_EMIT voltageChanged();
    if(oldR != resistance())
        Q_EMIT resistanceChanged();
    if(oldUnits != units())
        Q_EMIT unitsChanged();
    if(eNum != number())
        Q_EMIT numberChanged();
}

int CellState::number() const {
    return object()[STR_CHANNEL_STATUS_CELL_NUMBER].toInt(); 
}

QString CellState::voltage() const {
    return QString::number(object()[STR_CHANNEL_STATUS_CELL_VOLTAGE].toInt() / 1000.0, 'f', 2); 
}

double CellState::resistance() const {
    return object()[STR_CHANNEL_STATUS_CELL_RESISTANCE].toDouble(); 
}

QString CellState::units() const {
    return _units;
}

bool CellState::differsFrom(const CellState& other) const {
    return  voltage() != other.voltage() ||
            number() != other.number() ||
            resistance() != other.resistance() ||
            units() != other.units();
}


