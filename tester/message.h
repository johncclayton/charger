#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "nzmqt/nzmqt.hpp"

namespace nzmqt {

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(ZMQSocket* one, ZMQSocket* two, QObject *parent = 0);
    
signals:
    
public slots:
    
    void message(QList<QByteArray> msg);
    void notification(QList<QByteArray> msg);
    
private:
    ZMQSocket* _message;
    ZMQSocket* _subscribe;
};

}

#endif // MESSAGE_H
