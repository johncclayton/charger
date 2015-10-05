#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include <QObject>
#include <QTimerEvent>
#include <QDateTime>

namespace nzmqt {
    class ZMQSocket;
}

/**
 * @brief The MessageBus class provides an interface for the UI/Qml to talk to the 
 * back end services via ZeroMQ and JSON.  The interface is intended to be entirely
 * async in nature, the primary mechanism by which messages are sent/received is
 * the request/subscription channels. 
 * @see asyncRequest
 */
class MessageBus : public QObject
{
    Q_OBJECT
public:
    explicit MessageBus(nzmqt::ZMQSocket* pub, nzmqt::ZMQSocket* msg, QObject *parent = 0);
    virtual ~MessageBus();
    
    Q_PROPERTY(bool alive READ alive NOTIFY aliveChanged)
    
    bool alive() { return _alive; }
    
signals:
    void aliveChanged();
    void heartbeat();
    
    void notificationReceived(QString topic, QList<QByteArray> msg);
    void messageResponseReceived(QList<QByteArray> msg);
        
protected slots:
    void processMessageResponse(QList<QByteArray> msg);
    void processNotification(QList<QByteArray> msg);    
        
protected:
    /**
     * @brief timerEvent is used to work out how long we've gone without a heartbeat from the server
     * in order to set the connected/disconnected flag.  E.g. could be that tcp/ip comms is UP but
     * the server crashed - so the server sends something on /hearbeat every second.
     */
    void timerEvent(QTimerEvent* event);
    
    void setAlive(bool value);
    
private:
    
    /**
     * @brief asyncRequest publishes a request payload to the back end service and expects
     * the reply to appear at some point later on the provided topic (which can be anything, 
     * as long as the requestor has subscribed).  The reply will appear via the 
     * messageResponseReceived() signal.
     * @param responseTopic - the topic you want the reply to appear on
     * @param requestPayload - the message payload - hope you know what it should be.
     */    
    bool asyncRequest(QString requestPayload);

    nzmqt::ZMQSocket* _pub;
    nzmqt::ZMQSocket* _msg;
    bool _alive;
    QDateTime _lastHeartbeat;
};

#endif // MESSAGE_BUS_H
