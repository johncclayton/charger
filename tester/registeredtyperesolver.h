#ifndef REGISTEREDTYPERESOLVER_H
#define REGISTEREDTYPERESOLVER_H

#include <QObject>
#include <QHostAddress>
#include "../service/bonjour/bonjourrecord.h"
#include "../service/bonjour/bonjourservicebrowser.h"
#include "../service/bonjour/bonjourserviceresolver.h"

class RegisteredTypeResolver : public QObject
{
    Q_OBJECT
public:
    explicit RegisteredTypeResolver(QString type, QObject *parent = 0);
    
    void init();
    int port() const { return _port; }
    
signals:
    void serviceRemoved(QString type);
    void resolvedService(QString type, QHostInfo host, int port);
    void resolveError(QString type, int);
    
public slots:
    void bonjourResolutionError(int);
    void bonjourRecordAdded( const BonjourRecord& record );
    void bonjourRecordRemoved( const BonjourRecord& record );
    void bonjourServiceResolved(QHostInfo addr, int port);
    
private:
    QString _type;
    int _port;
    BonjourServiceBrowser* _browser;
    BonjourServiceResolver* _resolver;
};

#endif // REGISTEREDTYPERESOLVER_H
