#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include <QHostInfo>

#include "message_bus.h"
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
 */
class ClientMessagingController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(MessageBus* messageBus READ messageBus NOTIFY messageBusChanged)
    Q_PROPERTY(QString hostname READ hostname NOTIFY hostnameChanged)
    Q_PROPERTY(int publishPort READ publishPort NOTIFY publishPortChanged)
    Q_PROPERTY(int messagePort READ messagePort NOTIFY messagePortChanged)
    
    explicit ClientMessagingController(QObject *parent = 0);
    virtual ~ClientMessagingController();
    
    void init(int pub_port = 0, int msg_port = 0);
    
    MessageBus* messageBus() const { return _message_bus; }
    
signals:
    void messageBusChanged();
    
    void hostnameChanged();
    void publishPortChanged();
    void messagePortChanged();
        
protected slots:
//    void processNotificationReceived(QString topic, QList<QByteArray> msg);
    
public slots:
    void resolvedService(QString type, QHostInfo addr, int port);
    void serviceResolutionError(QString type, int err);    
    void serviceRemoved(QString type);
        
private:
    QString hostname() const { return _host; }
    void setHostname(QString value);
    
    int publishPort() const { return _pub_port; }
    void setPublishPort(int value);
    
    int messagePort() const { return _msg_port; }
    void setMessagePort(int value);
    
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
        
    QString _host;
    int _pub_port, _msg_port;
};

#endif // TESTCONTROLLER_H
