#ifndef BONJOURSERVICEREGISTER_H
#define BONJOURSERVICEREGISTER_H

#include <QObject>

class BonjourRecord;

class BonjourServiceRegister : public QObject
{
    Q_OBJECT
public:
    BonjourServiceRegister( QObject* parent = 0 );
    ~BonjourServiceRegister();

public Q_SLOTS:
    void registerService( const BonjourRecord& record, quint16 port );
    void registerService( const QString& name, const QString& type, const QString& domain, quint16 port );
    void registerService( const QString& name, const QString& type, quint16 port );
    void registerService( const QString& type, quint16 port );

private Q_SLOTS:
    void readyRead();

private:
    class Private;
    Private* const d;
};

#endif
