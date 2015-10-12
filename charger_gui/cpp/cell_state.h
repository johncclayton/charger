#ifndef CELLSTATE_H
#define CELLSTATE_H

#include <QObject>
#include <QJsonDocument>
#include <QSharedPointer>

class CellState : public QObject, private QJsonDocument
{
    Q_OBJECT
public:
    explicit CellState(QObject *parent = 0);
    
    Q_PROPERTY(double voltage READ cellVoltage NOTIFY voltageChanged)
    Q_PROPERTY(double resistance READ cellResistance NOTIFY resistanceChanged)
    Q_PROPERTY(QString units READ cellUnits WRITE setCellUnits NOTIFY unitsChanged)
    
    double cellVoltage() const;
    double cellResistance() const;
    QString cellUnits() const;
    
    bool differsFrom(const CellState& other) const;
    
signals:
    void unitsChanged();
    void voltageChanged();
    void resistanceChanged();
    
public slots:
    void setFromJson(QByteArray data);
    void setCellUnits(QString v) { _units = v; unitsChanged(); }
    
private: 
    QString _units;
};

typedef QSharedPointer<CellState> CellStatePtr;

#endif // CELLSTATE_H
