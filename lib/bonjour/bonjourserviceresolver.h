#ifndef BONJOURSERVICERESOLVER_H
#define BONJOURSERVICERESOLVER_H

#include <QObject>
#include <QHostInfo>

class BonjourRecord;

class BonjourServiceResolver : public QObject
{
    Q_OBJECT
public:
    BonjourServiceResolver( QObject* parent = 0 );
    ~BonjourServiceResolver();
    
    bool isResolving() const;

public Q_SLOTS:
    void resolveBonjourRecord( const BonjourRecord& record );

Q_SIGNALS:
    void bonjourResolverReady();
    void bonjourTXTRecordResolved( quint16 txtRecordLen, const unsigned char* pTxtRecord );
    void bonjourRecordResolved( const QHostInfo& hostInfo, int port);
    void error( int error);

private Q_SLOTS:
    void bonjourSocketReadyRead();
    void cleanupResolve();
    void finishConnect( const QHostInfo& hostInfo );

private:
    class Private;
    Private* const d;
};

#endif // BONJOURSERVICERESOLVER_H
