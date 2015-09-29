#include <QDebug>
#include <QList>
#include <QByteArray>
#include <QStringList>

#include "zmq/publisher.h"

using namespace nzmqt;

Publisher::Publisher(ZMQContext* ctx, QObject* owner) : SocketBase(ctx, ZMQSocket::TYP_PUB, owner) {
}

bool Publisher::bind(int port) {
    QString port_value("*");
    if(port != 0)
        port_value = QString::number(port);
    _socket->bindTo(QString("tcp://*:%1").arg(port_value));
    
    char temp[255];
    size_t value_len = 255;
    _socket->getOption(ZMQSocket::OPT_LAST_ENDPOINT, temp, &value_len);
    
    QStringList parts = QString::fromLatin1(temp).split(":");
    setPort(parts.last().toInt());
    
    return _port != 0;
}

void Publisher::publishOnTopic(QString topic, QString content) {
    QList< QByteArray > msg;
    msg += topic.toLocal8Bit();
    msg += content.toLocal8Bit();
    _socket->sendMessage(msg);
    
    //    qDebug() << "published on topic:" << topic << ":" << content;
}





