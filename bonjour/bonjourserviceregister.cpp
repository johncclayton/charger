#include "bonjourserviceregister.h"
#include "bonjourrecord.h"

#include <qendian.h>
#include <QSocketNotifier>

#include <dns_sd.h>

#include "moc_bonjourserviceregister.cpp"

class BonjourServiceRegister::Private
{
public:
    Private()
        : dnssref( 0 ),
          bonjourSocket( 0 )
    {
    }

public:
    static void DNSSD_API bonjourRegisterService( DNSServiceRef, DNSServiceFlags, DNSServiceErrorType error, const char* name,
                                                  const char* regtype, const char* domain, void* data )
    {
        Private* const p = static_cast< Private* >( data );
        if( error != kDNSServiceErr_NoError )
            return;
        p->record = BonjourRecord( QString::fromUtf8(name), QString::fromUtf8(regtype), QString::fromUtf8(domain) );
    }

    DNSServiceRef dnssref;
    QSocketNotifier* bonjourSocket;
    BonjourRecord record;
};

BonjourServiceRegister::BonjourServiceRegister( QObject* parent )
    : QObject( parent ),
      d( new Private)
{
}

BonjourServiceRegister::~BonjourServiceRegister()
{
	if( d->dnssref )
    {
        DNSServiceRefDeallocate( d->dnssref );
		d->dnssref = 0;
    }
	
	if( d->bonjourSocket)
	{
		delete d->bonjourSocket;
        d->bonjourSocket = 0;
	}
    delete d;
}

void BonjourServiceRegister::registerService( const BonjourRecord& record, quint16 port )
{
    const DNSServiceErrorType err = DNSServiceRegister( &d->dnssref, 0, 0, record.serviceName.isNull() ? 0 : record.serviceName.toUtf8().constData(), record.registeredType.toUtf8().constData(),
                                                        record.replyDomain.isEmpty() ? 0 : record.replyDomain.toUtf8().constData(), 0,
                                                        qToBigEndian( port ), 0, 0, Private::bonjourRegisterService, d );
    if( err != kDNSServiceErr_NoError )
        return;

    const int sock = DNSServiceRefSockFD( d->dnssref );
    if( sock == -1 )
        return;

    d->bonjourSocket = new QSocketNotifier( sock, QSocketNotifier::Read, this );
    connect( d->bonjourSocket, SIGNAL( activated( int ) ), this, SLOT( readyRead() ) );
}

void BonjourServiceRegister::registerService( const QString& name, const QString& type, const QString& domain, quint16 port )
{
    registerService( BonjourRecord( name, type, domain ), port );
}

void BonjourServiceRegister::registerService( const QString& name, const QString& type, quint16 port )
{
    registerService( BonjourRecord( name, type ), port );
}

void BonjourServiceRegister::registerService( const QString& type, quint16 port )
{
    registerService( BonjourRecord( QString(), type ), port );
}

void BonjourServiceRegister::readyRead()
{
    DNSServiceProcessResult( d->dnssref );
}
