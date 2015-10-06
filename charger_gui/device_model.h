#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QQmlContext>
#include <QVariantMap>
#include <QMap>
#include <QList>

#include "client_controller.h"

class DeviceModel : public QObject {
    Q_OBJECT
    
public:
    DeviceModel(QSharedPointer<ClientMessagingController> controller, QQmlContext* c, QObject *parent = 0);
    ~DeviceModel();

    typedef QMap<QString, QVariantMap> RawDataMap ;
    
    quint16 count() const { return _model.size(); }
    
    Q_PROPERTY(quint16 count READ count NOTIFY jsonDataChanged)
    
signals:
    void jsonDataChanged();
    
public slots:
    void resetModels();
    void messageBusAlive(bool alive);
    void deviceInfoUpdated(QString key, QVariantMap data);
    void devicesUpdated(QVariantMap data);
    void deviceAddedRemoved(bool added, QString key);
    
private:
    QSharedPointer<ClientMessagingController> _controller;
    QQmlContext* _ctx;
    RawDataMap _model;
};

#endif // DEVICEMODEL_H
