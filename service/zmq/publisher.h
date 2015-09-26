#ifndef ZMQ_PUBLISHER_H
#define ZMQ_PUBLISHER_H

#include <QObject>
#include <QSharedPointer>
#include "zmq/socketbase.h"

class Publisher : public SocketBase
{
    Q_OBJECT
public:
    explicit Publisher(nzmqt::ZMQContext* ctx, QObject* owner = 0);
    bool bind();
};

typedef QSharedPointer<Publisher> Publisher_ptr;

#endif // ZMQ_PUBLISHER_H
