#include <QCoreApplication>
#include <QStringList>
#include <QDebug>

#include "icharger_usb.h"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	usb_context c;
	if(!c) {
		qDebug() << "failed to init the USB context, cannot start up";
		return -1;
	} else {
        return app.exec();
    }
}
