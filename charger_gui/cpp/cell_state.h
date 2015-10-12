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
    
    Q_PROPERTY(double voltage READ voltage NOTIFY voltageChanged)
    Q_PROPERTY(double resistance READ resistance NOTIFY resistanceChanged)
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QString units READ units WRITE setCellUnits NOTIFY unitsChanged)
    
    double voltage() const;
    double resistance() const;
    int number() const;
    QString units() const;
    
    bool differsFrom(const CellState& other) const;
    
signals:
    void unitsChanged();
    void voltageChanged();
    void numberChanged();
    void resistanceChanged();
    
public slots:
    void setFromJson(QByteArray data);
    void setCellUnits(QString v) { _units = v; unitsChanged(); }
    
private: 
    QString _units;
};

typedef QSharedPointer<CellState> CellStatePtr;

#endif // CELLSTATE_H
