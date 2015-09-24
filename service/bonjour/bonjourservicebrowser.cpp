#include <string>

#include "bonjourservicebrowser.h"
#include "bonjourrecord.h"

#include "util/singleton.h"

#include <QSocketNotifier>
#include <QCoreApplication>

#include "moc_bonjourservicebrowser.cpp"

//this function will be called when the process terminates
static void bonjourThreadCleanup()
{
    BonjourServiceBrowserThread::instance()->quit();
    BonjourServiceBrowserThread::instance()->wait();
}


//callback function from bonjour service
void DNSSD_API BonjourServiceBrowserThread::bonjourBrowseReply( DNSServiceRef dnssref, DNSServiceFlags flags, quint32 , DNSServiceErrorType errorCode, 
											   const char* serviceName, const char *regType, const char* replyDomain, void*)
{
    instance()->bonjourResponse(dnssref, flags, errorCode, 
                                       QString::fromLocal8Bit(serviceName), QString::fromLocal8Bit(regType), QString::fromLocal8Bit(replyDomain));
}

BonjourServiceBrowserThread *BonjourServiceBrowserThread::instance()
{
    return FW::FWSingleton<BonjourServiceBrowserThread>::instance();
}


BonjourServiceBrowserThread::BonjourServiceBrowserThread()
{
    qAddPostRoutine(bonjourThreadCleanup);

    //this thread need to get events inside its own event loop
    moveToThread(this);
    
    connect(this, SIGNAL(listenerCreated(QString)), SLOT(slotListenerCreated(QString)));
    connect(this, SIGNAL(listenerPossiblyUseless(QString)), SLOT(slotListenerPossiblyUseless(QString)));
}
   

//this returns the list of already listed services
QList<BonjourRecord> BonjourServiceBrowserThread::addServiceBrowser(const QString &serviceType, BonjourServiceBrowser *browser)
{
    if (!isRunning())
        start();
    
    //this will be called from the GUI thread
    Q_ASSERT(currentThread() == qApp->thread());
    
    bool isNew = false;
    QList<BonjourRecord> ret;

    {
        QMutexLocker locker(&_mutex);
    
        isNew = !_serviceToListeners.contains(serviceType);
    
        BonjourListener &listener = _serviceToListeners[serviceType];
    
        connect(this, SIGNAL(bonjourRecordAdded(QString,BonjourRecord)), browser, SLOT(slotBonjourRecordAdded(QString,BonjourRecord)));
        connect(this, SIGNAL(bonjourRecordRemoved(QString,BonjourRecord)), browser, SLOT(slotBonjourRecordRemoved(QString,BonjourRecord)));
        connect(this, SIGNAL(error(QString,int)), browser, SLOT(slotError(QString,int)));

    
        ret = listener.bonjourRecords;
        listener.refCount++;
    }    

    //let's check if we just created the listener
    if (isNew)
        Q_EMIT listenerCreated(serviceType); //in which case, we need to create the dnssref (in the thread)
            
    return ret;
}

void BonjourServiceBrowserThread::removeServiceBrowser(const QString &serviceType, BonjourServiceBrowser *browser)
{
    //this will be called from the GUI thread
    Q_ASSERT(currentThread() == qApp->thread());

    bool emitSignal = false;
    {
        QMutexLocker locker(&_mutex);

        disconnect(this, SIGNAL(bonjourRecordAdded(QString,BonjourRecord)), browser, SLOT(slotBonjourRecordAdded(QString,BonjourRecord)));
        disconnect(this, SIGNAL(bonjourRecordRemoved(QString,BonjourRecord)), browser, SLOT(slotBonjourRecordRemoved(QString,BonjourRecord)));
        disconnect(this, SIGNAL(error(QString,int)), browser, SLOT(slotError(QString,int)));

        if (!_serviceToListeners.contains(serviceType))
            return; //this could happen if DNSServiceBrowse failed

        BonjourListener &listener = _serviceToListeners[serviceType];

        listener.refCount--;
        emitSignal = listener.refCount == 0;
    }

    if (emitSignal)
        Q_EMIT listenerPossiblyUseless(serviceType);
}

void BonjourServiceBrowserThread::slotListenerCreated(const QString &serviceType)
{
    //this must happen in the thread as it is very slow
    Q_ASSERT(currentThread() == this);
    
    DNSServiceRef dnssref = 0;
    
    const DNSServiceErrorType err = DNSServiceBrowse( &dnssref, 0, 0, qPrintable(serviceType), 0, bonjourBrowseReply, 0 );
    if( err != kDNSServiceErr_NoError ) {
        Q_EMIT error(serviceType, err );
        _serviceToListeners.remove(serviceType);
        return;
    } 
    const int sockfd = DNSServiceRefSockFD(dnssref);
    if( sockfd == -1 ) {
        Q_EMIT error(serviceType, kDNSServiceErr_Invalid );
        DNSServiceRefDeallocate( dnssref );
        return;
    }
    

    //we only lock the access to the map
    {
        QMutexLocker locker(&_mutex);
        
        if (!_serviceToListeners.contains(serviceType))
            return; //this can happen if a listener is registered and immediately after is removed
        
        BonjourListener &listener = _serviceToListeners[serviceType];
        Q_ASSERT(listener.dnssref == 0);
        
        listener.dnssref = dnssref;

        listener.socket = new QSocketNotifier(sockfd, QSocketNotifier::Read, this );
        connect( listener.socket, SIGNAL( activated( int ) ), this, SLOT( bonjourSocketReadyRead(int) ) );
    }

}

void BonjourServiceBrowserThread::slotListenerPossiblyUseless(const QString &serviceType)
{
    Q_ASSERT(currentThread() == this);

    DNSServiceRef dnssref = 0;
    {
        QMutexLocker locker(&_mutex);
   
        //we'll remove the service from the list
        if (_serviceToListeners.contains(serviceType)) {
            BonjourListener &listener = _serviceToListeners[serviceType];

            if (listener.refCount == 0) {
                delete listener.socket;
                dnssref = listener.dnssref;
                _serviceToListeners.remove(serviceType);
            }
        }
    }

    //we do the bonjour call outside of the mutex locking
    if (dnssref)
        DNSServiceRefDeallocate( dnssref );

}

void BonjourServiceBrowserThread::bonjourResponse(DNSServiceRef dnssref, DNSServiceFlags flags, DNSServiceErrorType errorCode, 
                                                      const QString &serviceName,  const QString &regType, const QString &replyDomain)
{
    //this must happen in the thread as it is very slow
    Q_ASSERT(currentThread() == this);

    QList< QPair<QString, BonjourRecord> > addedRecords, removedRecords;
    QList< QPair<QString, int> > errors;
    
    {
        QMutexLocker locker(&_mutex);

        for(QMap<QString, BonjourListener>::iterator it = _serviceToListeners.begin(); it != _serviceToListeners.end(); ++it) {
            if (it->dnssref == dnssref) {

                const QString &serviceType = it.key();

                if( errorCode != kDNSServiceErr_NoError ) {
                    errors += qMakePair(serviceType, errorCode );
                    return;
                }

                const BonjourRecord bonjourRecord( serviceName, regType, replyDomain );
                if( flags & kDNSServiceFlagsAdd ) {
                    it->bonjourRecords += bonjourRecord;
                    addedRecords += qMakePair(serviceType, bonjourRecord);
                } else {
                    it->bonjourRecords.removeOne(bonjourRecord);
                    removedRecords += qMakePair(serviceType, bonjourRecord);
                }

                break;
            }
        }
    }

    //we emit the signals outside of the mutex being locked
    for (auto err : errors) {
        Q_EMIT error(err.first, err.second);
    }

    for (auto removed : removedRecords) {
        Q_EMIT bonjourRecordRemoved(removed.first, removed.second);
    }
    for (auto added : addedRecords) {
        Q_EMIT bonjourRecordAdded(added.first, added.second);
    }
}

void BonjourServiceBrowserThread::bonjourSocketReadyRead(int sockfd)
{
    //this must happen in the thread as it is very slow
    Q_ASSERT(currentThread() == this);
    DNSServiceRef dnssref = 0;
    QString serviceType;

    {
        QMutexLocker locker(&_mutex);
        for(QMap<QString, BonjourListener>::const_iterator it = _serviceToListeners.begin(); it != _serviceToListeners.end(); ++it) {
            if (it->socket && it->socket->socket() == sockfd) {
                dnssref = it->dnssref;
                serviceType = it.key();
                break;
            }
        }
    }

    //it is safe to do that outside the lock because the deallocation anyway happens in this thread
    if (dnssref) {
        int err = DNSServiceProcessResult(dnssref); //this should provoke a call to bonjourBrowseReply
        if (kDNSServiceErr_NoError != err)
            Q_EMIT error(serviceType, err);
    }
}

BonjourServiceBrowser::BonjourServiceBrowser( QObject* parent)
    : QObject( parent )
{
    qRegisterMetaType<BonjourRecord>();
}

BonjourServiceBrowser::~BonjourServiceBrowser()
{
    Q_ASSERT(!_serviceType.isEmpty());
    BonjourServiceBrowserThread::instance()->removeServiceBrowser(_serviceType, this);
}

void BonjourServiceBrowser::browseForServiceType( const QString& serviceType )
{
    Q_ASSERT(_serviceType.isEmpty());
    _serviceType = serviceType;
    for (const BonjourRecord &record : BonjourServiceBrowserThread::instance()->addServiceBrowser(serviceType, this))
        Q_EMIT bonjourRecordAdded(record);
}	

void BonjourServiceBrowser::slotBonjourRecordAdded(const QString &serviceType,  const BonjourRecord& record )
{
    if (_serviceType == serviceType)
        Q_EMIT bonjourRecordAdded(record);
}

void BonjourServiceBrowser::slotBonjourRecordRemoved(const QString &serviceType,  const BonjourRecord& record )
{
    if (_serviceType == serviceType)
        Q_EMIT bonjourRecordRemoved(record);
}

void BonjourServiceBrowser::slotError(const QString &serviceType, int err)
{
    if (_serviceType == serviceType)
        Q_EMIT error(err);    
}
