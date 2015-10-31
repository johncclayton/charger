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
    explicit MessageBus(QObject *parent = 0);
    virtual ~MessageBus();
    
    Q_PROPERTY(bool alive READ alive NOTIFY aliveChanged)
    Q_PROPERTY(bool testing READ testing NOTIFY testingChanged)
    
    bool alive() const { return _alive; }
    void setAlive(bool value);

    bool testing() const { return _testing; }
    void setTesting(bool value);
    
    void getDevices() const;
    void getDeviceInformation(QString key) const;
    
    void setPublishSocket(nzmqt::ZMQSocket* s);
    void setMessageSocket(nzmqt::ZMQSocket* s);
    
    // for testing purposes - can inject the correct JSON as if it came from the wire
    void reinjectMessageResponse(QByteArray msg);
    
signals:
    void heartbeat();
    void aliveChanged(bool);
    void testingChanged(bool);
    
    void getDeviceResponse(QString key, QVariantMap resp);
    void getDevicesResponse(QVariantMap resp);
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
        
private:
    
    /**
     * @brief syncRequest publishes a request payload to the back end service and expects
     * the reply to immediately 
     * @param requestPayload - the message payload - hope you know what it should be.
     */    
    bool syncRequest(QByteArray requestPayload) const;
    bool syncRequest(QList<QByteArray> requestPayload) const;

    nzmqt::ZMQSocket* _pub;
    nzmqt::ZMQSocket* _msg;
    
    bool _alive, _testing;
    QDateTime _lastHeartbeat;
};

#endif // MESSAGE_BUS_H
