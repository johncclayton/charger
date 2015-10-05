#ifndef ZMQ_PUBLISHER_H
#define ZMQ_PUBLISHER_H

#include "zmq/socketbase.h"

#include <QObject>
#include <QSharedPointer>

/**
 * @brief The Publisher class is responsible for creating and binding the publisher ZeroMQ socket as
 * well as providing a public facing service that publishes messages.  The publisher doesn't define the
 * message format on the wire - it simply encodes messages into a QByteArray as <topic> + <data>.
 * @see publishOnTopic
 */
class Publisher : public SocketBase
{
    Q_OBJECT
public:
    explicit Publisher(nzmqt::ZMQContext* ctx, QObject* owner = 0);
    bool bind(int pub_port);
    
    void publishOnTopic(QByteArray topic, QByteArray content);
    void publish(QList<QByteArray> data);
};

typedef QSharedPointer<Publisher> Publisher_ptr;

#endif // ZMQ_PUBLISHER_H
