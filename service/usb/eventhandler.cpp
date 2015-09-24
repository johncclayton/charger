
#include <QtCore/QThread>
#include "libusb.h"
#include "eventhandler.h"

EventHandler::EventHandler(libusb_context *context, QObject *parent) :
    QObject(parent), timer(0), context(context)
{
    timer = startTimer(1);
}

void EventHandler::handle()
{
    libusb_handle_events_completed(this->context, 0);
}

void EventHandler::timerEvent(QTimerEvent *)
{
    QMetaObject::invokeMethod(this, "handle");
}


