#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client_controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
        
    ClientMessagingController controller;
    controller.init();
    
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("comms", &controller);
    engine.rootContext()->setContextProperty("charger", controller.charger());
    
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    
    return app.exec();
}

