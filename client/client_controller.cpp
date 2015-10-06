#include <QHostInfo>
#include <QUuid>

#include "client_controller.h"
#include "nzmqt/nzmqt.hpp"

using namespace nzmqt;

const QString publisher_service("_charger-service-pub._tcp");
const QString message_service("_charger-service-msg._tcp");

ClientMessagingController::ClientMessagingController(QObject *parent) : QObject(parent) {
    _ctx = createDefaultContext(this);
    _ctx->start();
    
    _pub_port = _msg_port = 0;
    _message_bus = new MessageBus(this);
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

void ClientMessagingController::init(int pub_port, int msg_port) {
    
    // kick off browsing for both service types but only when the ports are not specified.
    if(pub_port == 0 || msg_port == 0) {
        qDebug() << "listening...";
        _resolve_message->init();
        _resolve_subscribe->init();
    } else {
        qDebug() << QString("binding to localhost ports (you will need to have forwarded them appropriately through ssh, e.g. -L%1:<remote ip>:%2)...").arg(msg_port).arg(msg_port);
        QHostInfo localhost = QHostInfo();
        localhost.setHostName("localhost");
        
        resolvedService(message_service, localhost, msg_port);
        resolvedService(publisher_service, localhost, pub_port);
    }
}

void ClientMessagingController::closeRequestSocket() {
    if(_reqresp_socket) {
        _message_bus->setMessageSocket(0);
        _reqresp_socket->deleteLater();
        setMessagePort(0);
        setHostname(QString());
        qDebug() << "req/resp socket destroyed";    
    }
    _reqresp_socket = 0;
}

void ClientMessagingController::closeSubscribeSocket() {
    if(_subscribe_socket) {
        _message_bus->setPublishSocket(0);
        _subscribe_socket->deleteLater();
        setPublishPort(0);
        setHostname(QString());
        qDebug() << "subscribe socket destroyed";    
    }
    _subscribe_socket = 0;
}

ZMQSocket* ClientMessagingController::createSubscriberSocket() {
    _subscribe_socket = _ctx->createSocket(ZMQSocket::TYP_SUB, this);  
    _message_bus->setPublishSocket(_subscribe_socket);
    Q_EMIT messageBusChanged();
    return _subscribe_socket;
}

ZMQSocket* ClientMessagingController::createRequestSocket() {
    _reqresp_socket = _ctx->createSocket(ZMQSocket::TYP_DEALER, this);  
    QUuid ident = QUuid::createUuid();
    _reqresp_socket->setIdentity(ident.toString());
    _message_bus->setMessageSocket(_reqresp_socket);
    Q_EMIT messageBusChanged();
    return _reqresp_socket;
}

void ClientMessagingController::resolvedService(QString type, QHostInfo host, int port) {
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "For type:" << type << "the lookup failed:" << host.errorString();
        return;
    }

    setHostname(host.hostName());
    
    bool isSubscriber = false;
    ZMQSocket* s = 0;
    if(type == publisher_service) {
        closeSubscribeSocket();
        s = createSubscriberSocket();
        setPublishPort(port);
        isSubscriber = true;
    } else if(type == message_service) {
        closeRequestSocket();
        s = createRequestSocket();
        setMessagePort(port);
    }
    
    QString addr = QString("tcp://%1:%2").arg(host.hostName()).arg(port);
    qDebug() << "Connecting to:" << addr << "for:" << type;
    
    s->connectTo(addr);

    if(isSubscriber)
        s->subscribeTo("/");
}

void ClientMessagingController::serviceResolutionError(QString type, int err) {
    qDebug() << "failed to resolve:" << type << ", err:" << err;
}

void ClientMessagingController::serviceRemoved(QString type) {
    if(type == publisher_service) {
        closeSubscribeSocket();
    }
    else if(type == message_service) {
        closeRequestSocket();
    }
}

void ClientMessagingController::setHostname(QString value) { 
    if(value != _host) {
        _host = value; 
        Q_EMIT hostnameChanged(); 
    }
}

void ClientMessagingController::setPublishPort(int value) {
    if(value != _pub_port) {
        _pub_port = value;
        Q_EMIT publishPortChanged();
    }
}

void ClientMessagingController::setMessagePort(int value) {
    if(value != _msg_port) {
        _msg_port = value;
        Q_EMIT messagePortChanged();
    }
}
