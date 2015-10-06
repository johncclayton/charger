#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>
#include <QQmlContext>
#include <QMap>
#include <QList>

#include "icharger/charger_state.h"
#include "client_controller.h"

class DeviceModel : public QObject {
    Q_OBJECT
    
public:
    DeviceModel(QSharedPointer<ClientMessagingController> controller, 
                QQmlContext* ctx, QObject *parent = 0);
    ~DeviceModel();

    QList<ChargerState*> itemModel() const { return _model.values(); }
        
public slots:
    void messageBusAlive(bool alive);
    void deviceInfoUpdated(QString key, QVariantMap data);
    void devicesUpdated(QVariantMap data);
    void deviceAddedRemoved(bool added, QString key);
    
private:
    void replaceModel();
    
    QSharedPointer<ClientMessagingController> _controller;
    QMap<QString, ChargerState*> _model;
    QQmlContext* _ctx;
};

#endif // DEVICEMODEL_H
