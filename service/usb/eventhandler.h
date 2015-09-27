#ifndef USB_EVENTHANDLER_H
#define USB_EVENTHANDLER_H

#include <QtCore/QObject>
#include <QTimer>

struct libusb_context;
class QThread;

class UseQtEventDriver : public QObject
{
    Q_OBJECT

public:
    UseQtEventDriver(libusb_context *context, QObject *parent = 0);
    ~UseQtEventDriver();
    
    libusb_context *context;

public slots:
    void handle();

private:
    QTimer* timer;
};

#endif // USB_EVENTHANDLER_H
