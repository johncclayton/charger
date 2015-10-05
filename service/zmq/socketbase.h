#ifndef __SOCKETBASE_H
#define __SOCKETBASE_H

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
    
    virtual bool bind(int port) = 0;
    
signals:
    void portChanged(int port);
        
protected:
    nzmqt::ZMQSocket* _socket;
    int _port;
};

#endif // SOCKETBASE_H
