#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "nzmqt/nzmqt.hpp"

class MessageBus : public QObject
{
    Q_OBJECT
public:
    explicit MessageBus(nzmqt::ZMQSocket* pub, nzmqt::ZMQSocket* msg, QObject *parent = 0);
    virtual ~MessageBus();
    
signals:
    
public slots:
    void message(QList<QByteArray> msg);
    void notification(QList<QByteArray> msg);
};

#endif // MESSAGE_H
