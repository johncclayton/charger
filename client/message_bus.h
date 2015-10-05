#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include <QObject>
#include <QTimerEvent>
#include <QVariantMap>
#include <QDateTime>

namespace nzmqt {
    class ZMQSocket;
}

/**
 * @brief The MessageBus class provides an interface for the UI/Qml to talk to the 
 * back end services via ZeroMQ and JSON.  
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
    
    void deviceAddedRemoved(bool added, QString key);
    
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
     * @brief syncRequest publishes a request payload to the back end service and expects
     * the reply to immediately 
     * @param requestPayload - the message payload - hope you know what it should be.
     */    
    bool syncRequest(QString requestPayload);

    nzmqt::ZMQSocket* _pub;
    nzmqt::ZMQSocket* _msg;
    bool _alive;
    QDateTime _lastHeartbeat;
};

#endif // MESSAGE_BUS_H
