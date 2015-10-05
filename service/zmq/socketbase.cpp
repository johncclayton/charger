#include "socketbase.h"

SocketBase::SocketBase(nzmqt::ZMQContext* ctx, nzmqt::ZMQSocket::Type type, QObject* owner) : 
    QObject(owner), _socket(0), _port(0) 
{    
    _socket = ctx->createSocket(type);
}

SocketBase::~SocketBase() {
    if(_socket) {
        _socket->close();
        delete _socket;
        _socket = 0;
    }
    
    _port = 0;
}

int SocketBase::setPort(int port) {
    _port = port;
    Q_EMIT portChanged(_port);
    return _port;
}

int SocketBase::port() const {
    return _port;
}
