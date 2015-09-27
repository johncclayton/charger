
#include <QDebug>
#include <QtCore/QThread>

#include "libusb.h"
#include "eventhandler.h"

UseQtEventDriver::UseQtEventDriver(libusb_context *context, QObject *parent) :
    QObject(parent), timer(0), context(context)
{
}

void UseQtEventDriver::handle()
{
    qDebug() << "time genltemen!";
    libusb_handle_events_timeout(this->context, 0);
}

void UseQtEventDriver::init() {
    timer = startTimer(1);    
}

void UseQtEventDriver::timerEvent(QTimerEvent *)
{
    QMetaObject::invokeMethod(this, "handle");
}


