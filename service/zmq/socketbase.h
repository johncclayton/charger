#ifndef SOCKETBASE_H
#define SOCKETBASE_H

#include <QObject>
#include "nzmqt/nzmqt.hpp"

namespace nzmqt {
    class ZMQSocket;
    class ZMQContext;
}

class SocketBase : public QObject
{
    Q_OBJECT
    
public:
    SocketBase(nzmqt::ZMQContext* ctx, nzmqt::ZMQSocket::Type type, QObject* owner = 0);
    virtual ~SocketBase();
    
    int setPort(int port);
    int port() const;
    
    virtual bool bind() = 0;
    
signals:
    void port_changed(int port);
        
protected:
    nzmqt::ZMQSocket* _socket;
    int _port;
};

#endif // SOCKETBASE_H
