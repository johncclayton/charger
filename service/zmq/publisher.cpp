#include <QDebug>
#include <QStringList>
//#include <QJsonDocument>

#include "zmq/publisher.h"

using namespace nzmqt;

Publisher::Publisher(ZMQContext* ctx, QObject* owner) : SocketBase(ctx, ZMQSocket::TYP_PUB, owner) {
}

bool Publisher::bind() {
    _socket->bindTo("tcp://*:*");
    
    char temp[255];
    size_t value_len = 255;
    _socket->getOption(ZMQSocket::OPT_LAST_ENDPOINT, temp, &value_len);
    
    QStringList parts = QString::fromLatin1(temp).split(":");
    setPort(parts.last().toInt());
        
    return _port != 0;
}



    


