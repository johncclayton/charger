#ifndef REGISTEREDTYPERESOLVER_H
#define REGISTEREDTYPERESOLVER_H

#include <QHostInfo>
#include <QObject>

class BonjourServiceBrowser;
class BonjourServiceResolver;
class BonjourRecord;

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
