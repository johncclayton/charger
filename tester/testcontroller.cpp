#include <QHostInfo>
#include "testcontroller.h"

QHostAddress ip4(QHostAddress::AnyIPv4);

using namespace nzmqt;

TestController::TestController(QObject *parent) : QObject(parent) {
    _ctx = createDefaultContext(this);

    _messaging = 0;
    _message_socket = 0;
    _subscribe_socket = 0;
    
    _resolve_message = new RegisteredTypeResolver(QString("_charger-service-msg._tcp"));
    connect(_resolve_message, SIGNAL(serviceRemoved(QString)), this, SLOT(serviceRemoved(QString)));
    connect(_resolve_message, SIGNAL(resolvedService(QString,QHostInfo,int)), this, SLOT(resolvedService(QString,QHostInfo,int)));
    connect(_resolve_message, SIGNAL(resolveError(QString, int)), this, SLOT(serviceResolutionError(QString,int)));
    
    _resolve_subscribe = new RegisteredTypeResolver(QString("_charger-service-pub._tcp"));
    connect(_resolve_subscribe, SIGNAL(serviceRemoved(QString)), this, SLOT(serviceRemoved(QString)));
    connect(_resolve_subscribe, SIGNAL(resolvedService(QString,QHostInfo,int)), this, SLOT(resolvedService(QString,QHostInfo,int)));
    connect(_resolve_subscribe, SIGNAL(resolveError(QString,int)), this, SLOT(serviceResolutionError(QString,int)));
}

TestController::~TestController() {
    closeMessageSocket();
    closeSubscribeSocket();
}

void TestController::init() {
    // kick off browsing for both service types
    _resolve_message->init();
    _resolve_subscribe->init();
    qDebug() << "listening...";
}

void TestController::closeMessagingHandler() {
    if(_messaging) {
        delete _messaging;
        _messaging = 0;
    }
    
    if(_message_socket == 0 && _subscribe_socket == 0) {
        
    }
}

void TestController::closeMessageSocket() {
    _message_socket->close();
    delete _message_socket;
    _message_socket = 0;
    qDebug() << "messaging socket destroyed";    
    closeMessagingHandler();
}

void TestController::closeSubscribeSocket() {
    _subscribe_socket->close();
    delete _subscribe_socket;
    _subscribe_socket = 0;
    qDebug() << "subscribe socket destroyed";    
    closeMessagingHandler();
}

void TestController::resolvedService(QString type, QHostInfo addr, int port) {
    qDebug() << "type:" << type << "resolved to:" << addr.hostName() << " on port:" << port;
    if(type == QString("_charger-service-pub._tcp"))
        QHostInfo::lookupHost(addr.hostName(), this, SLOT(ip_resolvedForPub(QHostInfo)));
    else if(type == QString("_charger-service-msg._tcp"))
        QHostInfo::lookupHost(addr.hostName(), this, SLOT(ip_resolvedForMessaging(QHostInfo)));
}

void TestController::serviceResolutionError(QString type, int err) {
    qDebug() << "failed to resolve:" << type << ", err:" << err;
}

void TestController::serviceRemoved(QString type) {
    qDebug() << "type removed:" << type;   
    if(type == QString("_charger-service-pub._tcp")) {
        closeSubscribeSocket();
    }
    else if(type == QString("_charger-service-msg._tcp")) {
        closeMessageSocket();
    }
}

void TestController::ip_resolvedForPub(QHostInfo host) {
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    if(_subscribe_socket)
        closeSubscribeSocket();
    
    foreach (const QHostAddress &address, host.addresses()) {
        if(!_subscribe_socket) {
            _subscribe_socket = _ctx->createSocket(ZMQSocket::TYP_SUB, this);            
            QString addr = QString("tcp://%1:%2").arg(address.toString()).arg(_resolve_subscribe->port());
            qDebug() << "Connecting to publisher:" << addr;
            _subscribe_socket->connectTo(addr);
            _subscribe_socket->subscribeTo("");
            checkIsMessagingReady();
        }
    }
}

void TestController::ip_resolvedForMessaging(QHostInfo host) {
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    if(_message_socket)
        closeMessageSocket();
    
    foreach (const QHostAddress &address, host.addresses()) {
        if(!_message_socket) {
            _message_socket = _ctx->createSocket(ZMQSocket::TYP_DEALER, this);            
            QString addr = QString("tcp://%1:%2").arg(address.toString()).arg(_resolve_message->port());
            qDebug() << "Connecting to messaging:" << addr;
            _message_socket->connectTo(addr);
            checkIsMessagingReady();
        }
    }
}

void TestController::checkIsMessagingReady() {
    if(_messaging)
        return;
    
    if(_message_socket && _subscribe_socket) {
        _messaging = new Message(_subscribe_socket, _message_socket, this);
    }
}
