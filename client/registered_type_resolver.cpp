#include "bonjour/bonjourrecord.h"
#include "bonjour/bonjourservicebrowser.h"
#include "bonjour/bonjourserviceresolver.h"
#include "registered_type_resolver.h"

RegisteredTypeResolver::RegisteredTypeResolver(QString type, QObject *parent) : QObject(parent), _type(type)
{
    _browser = new BonjourServiceBrowser(this);
    _resolver = new BonjourServiceResolver(this);
    
    connect(_browser, SIGNAL(bonjourRecordAdded(BonjourRecord)), this, SLOT(bonjourRecordAdded(BonjourRecord)));
    connect(_browser, SIGNAL(bonjourRecordRemoved(BonjourRecord)), this, SLOT(bonjourRecordRemoved(BonjourRecord)));
    connect(_browser, SIGNAL(error(int)), this, SLOT(bonjourResolutionError(int)));
    
    connect(_resolver, SIGNAL(bonjourRecordResolved(QHostInfo,int)), this, SLOT(bonjourServiceResolved(QHostInfo,int)));
}

void RegisteredTypeResolver::init() {
    _browser->browseForServiceType(_type);
}

void RegisteredTypeResolver::bonjourResolutionError(int err) {
    Q_EMIT resolveError(_type, err);
}

void RegisteredTypeResolver::bonjourRecordAdded( const BonjourRecord& record ) {
    // now resolve it to host/port
    _resolver->resolveBonjourRecord(record);
}

void RegisteredTypeResolver::bonjourRecordRemoved( const BonjourRecord& record ) {
    Q_UNUSED(record);
    Q_EMIT serviceRemoved(_type);
}

void RegisteredTypeResolver::bonjourServiceResolved(QHostInfo addr, int port) {
    _port = port;
    Q_EMIT resolvedService(_type, addr, port);
}

