#ifndef USB_EVENTHANDLER_H
#define USB_EVENTHANDLER_H

#include <QtCore/QObject>

struct libusb_context;
class QThread;

class UseQtEventDriver : public QObject
{
    Q_OBJECT

public:
    UseQtEventDriver(libusb_context *context, QObject *parent = 0);

    void init();
    
    int timer;
    libusb_context *context;

public slots:
    void handle();

protected:
    virtual void timerEvent(QTimerEvent *);

private:

};

#endif // USB_EVENTHANDLER_H
