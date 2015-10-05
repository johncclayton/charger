#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>

#include "client_controller.h"
#include "qjsonmodel.h"

class DeviceModel : public QJsonModel {
    Q_OBJECT
    
public:
    DeviceModel(QSharedPointer<ClientMessagingController> controller, QObject *parent = 0);
    ~DeviceModel();
    
public slots:
    void messageBusInstantiated();
    
private:
    QSharedPointer<ClientMessagingController> _controller;
};

#endif // DEVICEMODEL_H
