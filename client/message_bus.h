#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include <QObject>
#include <QTimerEvent>

#include "device_info.h"
#include "channel_status.h"

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
    
signals:
    void channelStatusChanged(const ChannelStatus&);
    void deviceInfoChanged(const DeviceInfo&);    
    void messageResponseReceived(QString topic, QList<QByteArray> msg);
        
public slots:
    void messageReceived(QList<QByteArray> msg);
    void notificationReceived(QList<QByteArray> msg);    
    
protected:
    void timerEvent(QTimerEvent* event);
    
private:
    
    /**
     * @brief asyncRequest publishes a request payload to the back end service and expects
     * the reply to appear at some point later on the provided topic (which can be anything, 
     * as long as the requestor has subscribed).  The reply will appear via the 
     * messageResponseReceived() signal.
     * @param responseTopic - the topic you want the reply to appear on
     * @param requestPayload - the message payload - hope you know what it should be.
     */    
    bool asyncRequest(QString responseTopic, QString requestPayload);

    nzmqt::ZMQSocket* _pub;
    nzmqt::ZMQSocket* _msg;
};

#endif // MESSAGE_BUS_H
