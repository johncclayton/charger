#include <QSocketNotifier>
#include <QHostInfo>

#include <qendian.h>

#include "bonjourrecord.h"
#include "bonjourserviceresolver.h"

#include <dns_sd.h>

#include "moc_bonjourserviceresolver.cpp"

class BonjourServiceResolver::Private
{
public:
    Private( BonjourServiceResolver* q )
        : q( q ),
          dnssref( 0 ),
          bonjourSocket( 0 ),
          bonjourPort( -1 )
    {
    }

private:
    BonjourServiceResolver* const q;

public:
    static void DNSSD_API bonjourResolveReply(DNSServiceRef sdRef, DNSServiceFlags flags,
                                    uint32_t interfaceIndex, DNSServiceErrorType errorCode,
                                    const char *fullName, const char *hosttarget, quint16 port,
                                    quint16 txtRecordLen, const unsigned char* pTxtRecord, void *context);
    DNSServiceRef dnssref;
    QSocketNotifier* bonjourSocket;
    int bonjourPort;
};

BonjourServiceResolver::BonjourServiceResolver( QObject* parent )
    : QObject( parent ),
      d( new Private( this ) )
{
    connect( this, SIGNAL( error( int ) ), this, SLOT( cleanupResolve() ), Qt::QueuedConnection );
}

BonjourServiceResolver::~BonjourServiceResolver()
{
    cleanupResolve();
    delete d;
}

void BonjourServiceResolver::cleanupResolve()
{
	if( d->dnssref )
    {
        DNSServiceRefDeallocate( d->dnssref );
		d->dnssref = 0;
        d->bonjourPort = -1;
    }
	
	if(d->bonjourSocket)
	{
		delete d->bonjourSocket;
		d->bonjourSocket = 0;
	}

}

bool BonjourServiceResolver::isResolving() const
{
    return d->dnssref != 0;
}

void BonjourServiceResolver::resolveBonjourRecord( const BonjourRecord& record )
{
    if( isResolving() )
    {
        qWarning("resolve in process, aborting");
        return;
    }
    const DNSServiceErrorType err = DNSServiceResolve( &d->dnssref, 0, 0, record.serviceName.toUtf8().constData(), record.registeredType.toUtf8().constData(),
                                                       record.replyDomain.toUtf8().constData(), Private::bonjourResolveReply, d );
    if( err != kDNSServiceErr_NoError )
    {
        error( err );
    } 
    else 
    {
        const int sockfd = DNSServiceRefSockFD( d->dnssref );
        if( sockfd == -1 )
        {
            error( kDNSServiceErr_Invalid );
        } 
        else 
        {
            Q_ASSERT( d->bonjourSocket == 0 );
            d->bonjourSocket = new QSocketNotifier( sockfd, QSocketNotifier::Read, this );
            connect( d->bonjourSocket, SIGNAL( activated( int ) ), this, SLOT( bonjourSocketReadyRead() ) );
        }
    }
}

void BonjourServiceResolver::bonjourSocketReadyRead()
{
    // If you remove the following line, this breaks on Lion. Why, you ask?
    // Because this will then be done in the socket notifier destructor, which
    // will be run in another thread because of QHostInfo::lookupHost().
    // Very likely a bug in the Qt multi-threading code.
    d->bonjourSocket->setEnabled(false);

    const DNSServiceErrorType err = DNSServiceProcessResult( d->dnssref );
    if( err != kDNSServiceErr_NoError )
    {
        error( err );
    }
}

void BonjourServiceResolver::Private::bonjourResolveReply( DNSServiceRef, DNSServiceFlags, uint32_t, DNSServiceErrorType errorCode,
                                                           const char*, const char* hosttarget, quint16 port,
                                                           quint16 txtRecordLen, const unsigned char* pTxtRecord, void* context)
{
    Private* const serviceResolver = static_cast< Private* >( context );
    if( serviceResolver->bonjourPort != -1 || !serviceResolver->q->isResolving() )
        return;
    if( errorCode != kDNSServiceErr_NoError )
    {
        serviceResolver->q->error( errorCode );
        return;
    }
    Q_EMIT serviceResolver->q->bonjourTXTRecordResolved(txtRecordLen, pTxtRecord);
    serviceResolver->bonjourPort = qFromBigEndian( port );
    QHostInfo::lookupHost( QString::fromUtf8( hosttarget ), serviceResolver->q, SLOT( finishConnect( QHostInfo ) ) );
}

void BonjourServiceResolver::finishConnect( const QHostInfo& hostInfo )
{
    if(hostInfo.error() == QHostInfo::NoError)
    {
        Q_EMIT bonjourRecordResolved(hostInfo, d->bonjourPort);
    }
    else
    {
        Q_EMIT error(3);
    }

    cleanupResolve();
    Q_EMIT bonjourResolverReady();
}
