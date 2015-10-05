#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>
#include <QQmlContext>

#include "client_controller.h"
#include "device_model.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int pub_port = 0;
    int msg_port = 0;
    bool test = false;
    
    for(int index = 0; index < argc; ++index) {
        QString arg = app.arguments().at(index);
        if(arg == "-pub_port")
            pub_port = app.arguments().at(index + 1).toInt();
        if(arg == "-msg_port")
            msg_port = app.arguments().at(index + 1).toInt();
        if(arg == "-test")
            test = true;
    }
    
    int r = 0;
    {
        QSharedPointer<ClientMessagingController> controller(new ClientMessagingController);
        controller->init(pub_port, msg_port);
        
        DeviceModel model(controller);
        
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("comms", controller.data());
        engine.rootContext()->setContextProperty("deviceModel", &model);
        
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        
        r = app.exec();
    }
    
    return r;
}

