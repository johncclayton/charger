#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "nzmqt/nzmqt.hpp"

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(nzmqt::ZMQSocket* pub, nzmqt::ZMQSocket* msg, QObject *parent = 0);
    
signals:
    
public slots:
    void message(QList<QByteArray> msg);
    void notification(QList<QByteArray> msg);
};

#endif // MESSAGE_H
