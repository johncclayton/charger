#include <QHostInfo>
#include "client_controller.h"

using namespace nzmqt;
const QString publisher_service("_charger-service-pub._tcp");
const QString message_service("_charger-service-msg._tcp");

ClientMessagingController::ClientMessagingController(QObject *parent) : QObject(parent) {
    _ctx = createDefaultContext(this);
    _ctx->start();
    
    _message_bus = 0;
    
    _reqresp_socket = 0;
    _subscribe_socket = 0;
    
    _resolve_message = new RegisteredTypeResolver(message_service);
    connect(_resolve_message, SIGNAL(serviceRemoved(QString)), this, SLOT(serviceRemoved(QString)));
    connect(_resolve_message, SIGNAL(resolvedService(QString,QHostInfo,int)), this, SLOT(resolvedService(QString,QHostInfo,int)));
    connect(_resolve_message, SIGNAL(resolveError(QString, int)), this, SLOT(serviceResolutionError(QString,int)));
    
    _resolve_subscribe = new RegisteredTypeResolver(publisher_service);
    connect(_resolve_subscribe, SIGNAL(serviceRemoved(QString)), this, SLOT(serviceRemoved(QString)));
    connect(_resolve_subscribe, SIGNAL(resolvedService(QString,QHostInfo,int)), this, SLOT(resolvedService(QString,QHostInfo,int)));
    connect(_resolve_subscribe, SIGNAL(resolveError(QString,int)), this, SLOT(serviceResolutionError(QString,int)));
}

ClientMessagingController::~ClientMessagingController() {
    closeRequestSocket();
    closeSubscribeSocket();
}

void ClientMessagingController::init() {
    // kick off browsing for both service types
    _resolve_message->init();
    _resolve_subscribe->init();
    
    Q_EMIT stateChanged(CS_DISCOVERY);
    
    qDebug() << "listening...";
}

void ClientMessagingController::closeMessagingHandler() {
    if(_message_bus) {
        qDebug() << "closing the message bus";
        delete _message_bus;
        _message_bus = 0;

        Q_EMIT stateChanged(CS_DISCOVERY);
    }
}

void ClientMessagingController::closeRequestSocket() {
    if(_reqresp_socket)
        _reqresp_socket->deleteLater();
    _reqresp_socket = 0;
    qDebug() << "req/resp socket destroyed";    
    closeMessagingHandler();
}

void ClientMessagingController::closeSubscribeSocket() {
    if(_subscribe_socket)
        _subscribe_socket->deleteLater();
    _subscribe_socket = 0;
    qDebug() << "subscribe socket destroyed";    
    closeMessagingHandler();
}

ZMQSocket* ClientMessagingController::createSubscriberSocket() {
    _subscribe_socket = _ctx->createSocket(ZMQSocket::TYP_SUB, this);  
    return _subscribe_socket;
}

ZMQSocket* ClientMessagingController::createRequestSocket() {
    _reqresp_socket = _ctx->createSocket(ZMQSocket::TYP_DEALER, this);  
    return _reqresp_socket;
}

void ClientMessagingController::resolvedService(QString type, QHostInfo host, int port) {
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "For type:" << type << " the lookup failed:" << host.errorString();
        return;
    }
    
    bool isSubscriber = false;
    ZMQSocket* s = 0;
    if(type == publisher_service) {
        closeSubscribeSocket();
        s = createSubscriberSocket();
        isSubscriber = true;
    } else if(type == message_service) {
        closeRequestSocket();
        s = createRequestSocket();
    }
    
    QString addr = QString("tcp://%1:%2").arg(host.hostName()).arg(port);
    qDebug() << "Connecting to:" << addr;
    s->connectTo(addr);
    
    if(isSubscriber)
        s->subscribeTo("/`");

    checkIsMessageBusReady();
}

void ClientMessagingController::serviceResolutionError(QString type, int err) {
    qDebug() << "failed to resolve:" << type << ", err:" << err;
}

void ClientMessagingController::serviceRemoved(QString type) {
    qDebug() << "type removed:" << type;   
    if(type == publisher_service) {
        closeSubscribeSocket();
    }
    else if(type == message_service) {
        closeRequestSocket();
    }
}

void ClientMessagingController::checkIsMessageBusReady() {
    if(_message_bus)
        return;
    
    if(_reqresp_socket && _subscribe_socket) {
        _message_bus = new MessageBus(_subscribe_socket, _reqresp_socket, this);
        Q_EMIT stateChanged(CS_CONNECTED);
    }
}
