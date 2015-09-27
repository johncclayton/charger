#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include <QHostInfo>
#include <QHostAddress>

#include "message.h"
#include "registeredtyperesolver.h"
#include "nzmqt/nzmqt.hpp"

class TestController : public QObject
{
    Q_OBJECT
public:
    explicit TestController(QObject *parent = 0);
    virtual ~TestController();
    
    void init();
signals:
    
public slots:
    void resolvedService(QString type, QHostInfo addr, int port);
    void serviceResolutionError(QString type, int err);    
    void serviceRemoved(QString type);
    
private slots:
    void ipresolvedForPub(QHostInfo);
    void ipresolvedForMessaging(QHostInfo);
    
private:
    void closeMessageSocket();
    void closeSubscribeSocket();
    
    void closeMessagingHandler();
    void checkIsMessagingReady();
    
    nzmqt::ZMQContext* _ctx;
    nzmqt::ZMQSocket* _message_socket;
    nzmqt::ZMQSocket* _subscribe_socket;

    RegisteredTypeResolver* _resolve_message;
    RegisteredTypeResolver* _resolve_subscribe;
    
    Message* _messaging;
};

#endif // TESTCONTROLLER_H
