#ifndef ZMQ_PUBLISHER_H
#define ZMQ_PUBLISHER_H

#include <QObject>
#include "zmq/socketbase.h"

class ZMQ_Publisher : public SocketBase
{
    Q_OBJECT
public:
    explicit ZMQ_Publisher(nzmqt::ZMQContext* ctx, QObject* owner = 0);
    bool bind();
};

#endif // ZMQ_PUBLISHER_H
