#ifndef SYSTEMSTORAGE_H
#define SYSTEMSTORAGE_H

#include <QObject>
#include <QJsonDocument>

class SystemStorage : public QObject, private QJsonDocument
{
    Q_OBJECT
public:
    explicit SystemStorage(QObject *parent = 0);
    
signals:
    
public slots:
};

#endif // SYSTEMSTORAGE_H
