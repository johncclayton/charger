#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>
#include <QQmlContext>
#include <QtQml>

#include "client_controller.h"

#include "device_info.h"
#include "channel_status.h"
#include "system_storage.h"
#include "device_model.h"
#include "cell_state.h"
#include "channel_view_model.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    int pub_port = 0;
    int msg_port = 0;
    QString data_dir;
    
    for(int index = 0; index < argc; ++index) {
        QString arg = app.arguments().at(index);
        if(arg == "-pub_port")
            pub_port = app.arguments().at(index + 1).toInt();
        if(arg == "-msg_port")
            msg_port = app.arguments().at(index + 1).toInt();
        if(arg == "-data_dir")
            data_dir = app.arguments().at(index + 1);
    }
    
    qmlRegisterType<SystemStorage>("com.coderage.messaging", 1, 0, "SystemStorage");
    qmlRegisterType<CellState>("com.coderage.messaging", 1, 0, "CellState");
    qmlRegisterType<ChannelStatus>("com.coderage.messaging", 1, 0, "ChannelStatus");
    qmlRegisterType<DeviceInfo>("com.coderage.messaging", 1, 0, "DeviceInfo");
    qmlRegisterType<ChannelViewModel>("com.coderage.messaging", 1, 0, "ChannelViewModel");
    
    int r = 0;
    {
        QSharedPointer<ClientMessagingController> controller(new ClientMessagingController);
        
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("comms", controller.data());

        // Listens to events from the message bus and updates an in-memory
        // JSON model structure that's exposed to QML via pixie dust.
        DeviceModel model(controller, engine.rootContext());
        
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        controller->init(pub_port, msg_port, data_dir);
        
        r = app.exec();
    }
    
    return r;
}

