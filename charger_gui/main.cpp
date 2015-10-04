#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>
#include <QQmlContext>

#include "client_controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    int r = 0;
    {
        QSharedPointer<ClientMessagingController> controller(new ClientMessagingController);
        controller->init();
        
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("comms", controller.data());
        engine.rootContext()->setContextProperty("charger", controller->charger());
        
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        
        r = app.exec();
    }
    
    return r;
}

