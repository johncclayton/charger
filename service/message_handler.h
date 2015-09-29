#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <QObject>
#include <QByteArray>
#include <QList>

#include "zmq/socketbase.h"

/**
 * @brief The MessageHandler class is a zero-mq message router/dealer.  It receives requests to do stuff with the
 * attached chargers and uses the device registry as well as the publishing service to satisfy those tasks.  All
 * GUI apps talk to this sucker.
 * 
 * This class is also (indirectly) responsible for translating the underlying data structures into easier 
 * to consume JSON messages.
 */
class MessageHandler : public SocketBase
{
    Q_OBJECT
    
public:
    explicit MessageHandler(nzmqt::ZMQContext* ctx, QObject *parent = 0);
    bool bind(int port);    
    
public slots:
    void message_received(QList<QByteArray> msg);
};

#endif // MESSAGE_HANDLER_H
