#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include <QHostInfo>
#include <QMetaType>

#include "message_bus.h"
#include "charger_state.h"
#include "registeredtyperesolver.h"

namespace nzmqt {
    class ZMQSocket;
    class ZMQContext;
}

/**
 * @brief The ClientMessagingController class discovers the required zmq subcscription and
 * req/resp endpoints and connects/configures the appropriate sockets to the MessageBus class.
 * It continues to monitor the bonjour information and if the sockets change or go down it 
 * will re-create the messaging bus instance.
 * 
 * There are two states, CS_DISCOVERY and CS_CONNECTED.  Only when both endpoints to zmq
 * have been discovered and connected does the state change to CS_CONNECTED.  If the socket
 * endpoints (according to bonjour) change, the class goes back into the CS_DISCOVERY state.
 */
class ClientMessagingController : public QObject
{
    Q_OBJECT
public:
    enum State {
        DISCOVERY = 0,
        CONNECTED = 1
    };
    
    Q_ENUMS(State)

    Q_PROPERTY(MessageBus* messageBus READ messageBus NOTIFY onMessageBusChanged)
    Q_PROPERTY(State state READ state WRITE setState NOTIFY onStateChanged)
    Q_PROPERTY(ChargerState charger READ charger NOTIFY onChargerChanged)
    Q_PROPERTY(QString hostname READ hostname NOTIFY onHostnameChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY onConnectedChanged)
    
    explicit ClientMessagingController(QObject *parent = 0);
    virtual ~ClientMessagingController();
    
    void init(int pub_port = 0, int msg_port = 0);
    
    MessageBus* messageBus() const { return _message_bus; }
    ChargerState* charger() const { return _charger_state; }
    
    State state() const { return _state; }
    void setState(State s) { _state = s; Q_EMIT onStateChanged(s); }

signals:
    void onMessageBusChanged();
    void onChargerChanged();
    void onStateChanged(ClientMessagingController::State);
    void onHostnameChanged(QString newName);
    void onConnectedChanged();
    
protected slots:
    void routeStatusUpdated(const ChannelStatus& status);
    
public slots:
    void resolvedService(QString type, QHostInfo addr, int port);
    void serviceResolutionError(QString type, int err);    
    void serviceRemoved(QString type);
        
private:
    bool connected() const { return _state == CONNECTED; }
    QString hostname() const { return _host; }
    void setHostname(QString value) { _host = value; Q_EMIT onHostnameChanged(_host); }
    
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
    ChargerState* _charger_state;
    
    State _state;
    
    QString _host;
};

//Q_DECLARE_METATYPE(ClientMessagingController::State)

#endif // TESTCONTROLLER_H
