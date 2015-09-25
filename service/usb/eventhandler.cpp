
#include <QtCore/QThread>
#include "libusb.h"
#include "eventhandler.h"

UseQtEventDriver::UseQtEventDriver(libusb_context *context, QObject *parent) :
    QObject(parent), timer(0), context(context)
{
    timer = startTimer(1);
}

void UseQtEventDriver::handle()
{
    libusb_handle_events_completed(this->context, 0);
}

void UseQtEventDriver::timerEvent(QTimerEvent *)
{
    QMetaObject::invokeMethod(this, "handle");
}


