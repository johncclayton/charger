#include <QDebug>
#include <QStringList>

#include "nzmqt/nzmqt.hpp"
#include "zmq/zmq_publisher.h"

using namespace nzmqt;

ZMQ_Publisher::ZMQ_Publisher(ZMQContext* ctx, QObject* owner) : QObject(owner), _socket(0), _port(0)
{
    _socket = ctx->createSocket(ZMQSocket::TYP_PUB, this);
}

ZMQ_Publisher::~ZMQ_Publisher() {
    delete _socket;
    _socket = 0;
}

bool ZMQ_Publisher::bind() {
    _port = 0;
    _socket->bindTo("tcp://127.0.0.1:*");
    
    char temp[255];
    size_t value_len = 255;
    _socket->getOption(ZMQSocket::OPT_LAST_ENDPOINT, temp, &value_len);
    
    QStringList parts = QString::fromLatin1(temp).split(":");
    _port = parts.last().toInt();
    
    Q_EMIT port_changed(_port);
    
    return _port != 0;
}

int ZMQ_Publisher::port() const {
    return _port;
}
    


