#ifndef BONJOURSERVICEBROWSER_H
#define BONJOURSERVICEBROWSER_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QMutex>
#include <dns_sd.h>

#include "bonjourrecord.h"

class BonjourServiceBrowser;
class QSocketNotifier;

//Warning: this is an internal class for BonjourServiceBrowser
//it is not intended to be used outside of it
class BonjourServiceBrowserThread : public QThread
{
    Q_OBJECT
public:
    BonjourServiceBrowserThread();
        
    QList<BonjourRecord>  addServiceBrowser(const QString &serviceType, BonjourServiceBrowser *browser);
    void removeServiceBrowser(const QString &serviceType, BonjourServiceBrowser *browser);
    
    static BonjourServiceBrowserThread *instance();
    
Q_SIGNALS:
    void bonjourRecordAdded(const QString &serviceType, const BonjourRecord& record );
    void bonjourRecordRemoved(const QString &serviceType, const BonjourRecord& record );
    void error(const QString &serviceType, int error);

    //internal
    void listenerCreated(const QString &serviceType);
    void listenerPossiblyUseless(const QString &serviceType);
    
protected Q_SLOTS:
    void slotListenerCreated(const QString &serviceType);
    void slotListenerPossiblyUseless(const QString &serviceType);
    void bonjourSocketReadyRead(int sockfd);
    
private:
    void bonjourResponse(DNSServiceRef dnssref, DNSServiceFlags flags, DNSServiceErrorType errorCode, 
                             const QString &serviceName,  const QString &regType, const QString &replyDomain);
    
    //callback function
    static void DNSSD_API bonjourBrowseReply( DNSServiceRef dnssref,  DNSServiceFlags flags,  quint32 , 
                                                         DNSServiceErrorType errorCode, 
                                                         const char* serviceName, 
                                                         const char *regType,
                                                         const char* replyDomain, 
                                                         void*);

    QMutex _mutex;
    
    struct BonjourListener {
        BonjourListener() : socket(0), dnssref(0), refCount(0) { }
        
        QSocketNotifier *socket; //socket for notification
        DNSServiceRef dnssref;
        int refCount;
        QList< BonjourRecord > bonjourRecords;
    };
    
    QMap<QString, BonjourListener> _serviceToListeners;

};

class BonjourServiceBrowser : public QObject
{
    Q_OBJECT
public:
    BonjourServiceBrowser( QObject* parent);
    ~BonjourServiceBrowser();
    
    void browseForServiceType( const QString& serviceType );
    
Q_SIGNALS:
    void bonjourRecordAdded( const BonjourRecord& record );
    void bonjourRecordRemoved( const BonjourRecord& record );
    void error( int err );

private Q_SLOTS:
    void slotBonjourRecordAdded(const QString &serviceType, const BonjourRecord& record );
    void slotBonjourRecordRemoved(const QString &serviceType, const BonjourRecord& record );
    void slotError(const QString &serviceType, int err);
    
private:
    QString _serviceType;
};

#endif // BONJOURSERVICEBROWSER_H
