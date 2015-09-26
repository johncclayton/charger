#ifndef ZMQ_PUBLISHER_H
#define ZMQ_PUBLISHER_H

#include <QObject>

namespace nzmqt {
    class ZMQSocket;
    class ZMQContext;
}

class ZMQ_Publisher : public QObject
{
    Q_OBJECT
public:
    explicit ZMQ_Publisher(nzmqt::ZMQContext* ctx, QObject* owner = 0);
    virtual ~ZMQ_Publisher();

    bool bind();
    int port() const;
    
signals:
    void port_changed(int port);
    
public slots:
    //void publish_icharger_state(QString description, QString serial, bool connected);
    
private:
    nzmqt::ZMQSocket* _socket;
    int _port;
};

#endif // ZMQ_PUBLISHER_H
