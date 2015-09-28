#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include <QHostInfo>
#include <QMetaType>
#include <QHostAddress>

#include "message_bus.h"
#include "registeredtyperesolver.h"
#include "nzmqt/nzmqt.hpp"

class ClientMessagingController : public QObject
{
    Q_OBJECT
public:
    explicit ClientMessagingController(QObject *parent = 0);
    virtual ~ClientMessagingController();
    
    void init();
    
    enum State {
        CS_DISCOVERY = 0,
        CS_FOUND_PUBLISHER = 1,
        CS_FOUND_MESSAGER = 2,
        CS_CONNECTED
    };

signals:
    void stateChanged(ClientMessagingController::State);    
    
public slots:
    void resolvedService(QString type, QHostInfo addr, int port);
    void serviceResolutionError(QString type, int err);    
    void serviceRemoved(QString type);
        
private:
   
    nzmqt::ZMQSocket* createSubscriberSocket();
    nzmqt::ZMQSocket* createRequestSocket();
    
    void closeRequestSocket();
    void closeSubscribeSocket();
    
    void closeMessagingHandler();
    void checkIsMessageBusReady();
    
    nzmqt::ZMQContext* _ctx;
    nzmqt::ZMQSocket* _reqresp_socket;
    nzmqt::ZMQSocket* _subscribe_socket;

    RegisteredTypeResolver* _resolve_message;
    RegisteredTypeResolver* _resolve_subscribe;
    
    MessageBus* _message_bus;
};

Q_DECLARE_METATYPE(ClientMessagingController::State)

#endif // TESTCONTROLLER_H
