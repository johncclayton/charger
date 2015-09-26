#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <QObject>

/**
 * @brief The MessageHandler class is a zero-mq message router/dealer.  It receives requests to do stuff with the
 * attached chargers and uses the device registry as well as the publishing service to satisfy those tasks.  All
 * GUI apps talk to this sucker.
 * 
 * This class is also (indirectly) responsible for translating the underlying data structures into easier 
 * to consume JSON messages.
 */
class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = 0);
    
signals:
    
public slots:
};

#endif // MESSAGE_HANDLER_H
