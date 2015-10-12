#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QQmlContext>
#include <QVariantMap>
#include <QMap>

#include <QList>

#include "client_controller.h"
class DeviceInfo;

class DeviceModel : public QObject {
    Q_OBJECT
    
public:
    Q_PROPERTY(int count READ getCount NOTIFY jsonDataChanged)
    
    DeviceModel(QSharedPointer<ClientMessagingController> controller, QQmlContext* c, QObject *parent = 0);
    ~DeviceModel();

    typedef QMap<QString, QVariantMap> RawDataMap ;
    
    int getCount() const { return _model.size(); }
    
    Q_INVOKABLE DeviceInfo* getDeviceInfo(QString key);
        
signals:
    void jsonDataChanged();
    void deviceAddedRemoved(bool added, QString key);
    void deviceInfoUpdated(QString key);
    
public slots:
    void resetModels();
    void messageBusAlive(bool alive);
    void processDeviceInfoUpdated(QString key, QVariantMap data);
    void processDevicesUpdated(QVariantMap data);
    void processDeviceAddedRemoved(bool added, QString key);
    
protected:
    void timerEvent(QTimerEvent* event);
    
private:
    QSharedPointer<ClientMessagingController> _controller;
    QQmlContext* _ctx;
    RawDataMap _model;
    QObjectList _devices;    
};

#endif // DEVICEMODEL_H
