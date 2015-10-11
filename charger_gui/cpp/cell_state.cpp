#include <QByteArray>
#include <QJsonObject>

#include "cpp/cell_state.h"
#include "icharger/icharger_message_keys.h"

CellState::CellState(QObject *parent) : QObject(parent) {    
}

void CellState::setFromJson(QByteArray data) {
    setObject( QJsonDocument::fromJson(data).object() );    
}

quint32 CellState::cellNumber() const {
    return object()[STR_CHANNEL_STATUS_CELL_NUMBER].toInt(); 
    
}

QString CellState::cellValue() const {
    return object()[STR_CHANNEL_STATUS_CELL_VOLTAGE].toString(); 
}

QString CellState::cellUnits() const {
    return _units;
    
}

