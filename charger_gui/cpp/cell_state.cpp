#include <QByteArray>
#include <QJsonObject>
#include <QDebug> 

#include "cpp/cell_state.h"
#include "icharger/icharger_message_keys.h"

CellState::CellState(QObject *parent) : QObject(parent) {    
}

void CellState::setFromJson(QByteArray data) {
    QString oldValue = voltage();
    QString oldR = resistance();
    int eNum = number();
    
    setObject( QJsonDocument::fromJson(data).object() );    
    
    if(oldValue != voltage())
        Q_EMIT voltageChanged();
    if(oldR != resistance())
        Q_EMIT resistanceChanged();
    if(eNum != number())
        Q_EMIT numberChanged();
}

int CellState::number() const {
    return object()[STR_CHANNEL_STATUS_CELL_NUMBER].toInt(); 
}

QString CellState::voltage() const {
    return QString::number(object()[STR_CHANNEL_STATUS_CELL_VOLTAGE].toInt() / 1000.0, 'f', 2); 
}

QString CellState::resistance() const {
    return QString::number(object()[STR_CHANNEL_STATUS_CELL_RESISTANCE].toDouble(), 'f', 2); 
}

bool CellState::differsFrom(const CellState& other) const {
    return  voltage() != other.voltage() ||
            number() != other.number() ||
            resistance() != other.resistance();
}


