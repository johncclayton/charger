#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>

#include "client_controller.h"
#include "qjsonmodel.h"

class DeviceModel : public QObject {
    Q_OBJECT
    
public:
    DeviceModel(QSharedPointer<ClientMessagingController> controller, 
                QObject *parent = 0);
    ~DeviceModel();

    QAbstractItemModel* itemModel() const { return _model; }
        
public slots:
    void messageBusAlive(bool alive);
    void deviceInfoUpdated(QString key, QVariantMap data);
    void deviceAddedRemoved(bool added, QString key);
    
private:
    QSharedPointer<ClientMessagingController> _controller;
    QJsonModel* _model;
};

#endif // DEVICEMODEL_H
