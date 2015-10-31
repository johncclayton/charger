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
    
    Q_PROPERTY(QString voltage READ voltage NOTIFY voltageChanged)
    Q_PROPERTY(QString resistance READ resistance NOTIFY resistanceChanged)
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    
    QString voltage() const;
    QString resistance() const;
    int number() const;
    
    bool differsFrom(const CellState& other) const;
    
signals:
    void voltageChanged();
    void numberChanged();
    void resistanceChanged();
    
public slots:
    void setFromJson(QByteArray data);
};

typedef QSharedPointer<CellState> CellStatePtr;

#endif // CELLSTATE_H
