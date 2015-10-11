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
    
    Q_PROPERTY(quint32 number READ cellNumber)
    Q_PROPERTY(QString value READ cellValue)
    Q_PROPERTY(QString units READ cellUnits WRITE setCellUnits NOTIFY unitsChanged)
    
    quint32 cellNumber() const;
    QString cellValue() const;
    QString cellUnits() const;
    
signals:
    void unitsChanged();
    
public slots:
    void setFromJson(QByteArray data);
    
    void setCellUnits(QString v) { _units = v; unitsChanged(); }
    
private: 
    QString _units;
};

typedef QSharedPointer<CellState> CellStatePtr;

#endif // CELLSTATE_H
