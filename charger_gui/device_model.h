#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>
#include <QMap>
#include <QList>

#include "client_controller.h"

class DeviceModel : public QObject {
    Q_OBJECT
    
public:
    DeviceModel(QSharedPointer<ClientMessagingController> controller, QObject *parent = 0);
    ~DeviceModel();

    QByteArray jsonData() const;
    quint16 deviceCount() const { return _model.size(); }
    
    Q_PROPERTY(QByteArray jsonData READ jsonData NOTIFY jsonDataChanged)
    Q_PROPERTY(quint16 count READ deviceCount NOTIFY jsonDataChanged)
    
signals:
    void jsonDataChanged();
    
public slots:
    void messageBusAlive(bool alive);
    void deviceInfoUpdated(QString key, QVariantMap data);
    void devicesUpdated(QVariantMap data);
    void deviceAddedRemoved(bool added, QString key);
    
private:
    QSharedPointer<ClientMessagingController> _controller;
    QMap<QString, QVariantMap> _model;
};

#endif // DEVICEMODEL_H
