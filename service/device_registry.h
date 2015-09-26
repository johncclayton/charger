#ifndef __DEV_REG_H
#define __DEV_REG_H

#include <QObject>

/**
 * Responsible for instantiating and keeping track of all currently
 * connected devices in the system.  
 */
class DeviceRegistry : public QObject {

Q_OBJECT

public:
	DeviceRegistry(QObject* owner = 0);
	virtual ~``DeviceRegistry();

slots:
	

signals:

};

#endif

