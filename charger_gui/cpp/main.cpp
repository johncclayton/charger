#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>
#include <QQmlContext>
#include <QQmlError>
#include <QtQml>
#include <QFileSystemWatcher>

#include "client_controller.h"

#include "format.h"
#include "device_info.h"
#include "channel_status.h"
#include "system_storage.h"
#include "device_model.h"
#include "cell_state.h"
#include "channel_view_model.h"

static QObject *format_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    Format *example = new Format();
    return example;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    bool watch = false;
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
        if(arg == "-watch")
            watch = true;
    }
    
    // use this when testing: 
    // -data_dir /Users/john/src/icharger.git/test_data -msg_port 23014 -pub_port 23013
    
    // TODO: put into the icharger namespace
    qmlRegisterType<SystemStorage>("com.coderage.messaging", 1, 0, "SystemStorage");
    qmlRegisterType<CellState>("com.coderage.messaging", 1, 0, "CellState");
    qmlRegisterType<ChannelStatus>("com.coderage.messaging", 1, 0, "ChannelStatus");
    qmlRegisterType<DeviceInfo>("com.coderage.messaging", 1, 0, "DeviceInfo");
    qmlRegisterType<ChannelViewModel>("com.coderage.messaging", 1, 0, "ChannelViewModel");
    qmlRegisterSingletonType<Format>("com.coderage.messaging", 1, 0, "Format", format_provider);

    QFileSystemWatcher w;
    QString rootPath("/Users/john/src/icharger.git");
    QString ichargerPath = QString("%1%2charger_gui/").arg(rootPath, QDir::separator());

    if(watch) {
        qDebug() << "checking path for:" << rootPath;

        QDirIterator itr(rootPath, QDirIterator::Subdirectories);
        while(itr.hasNext()) {
            itr.next();
            
            QFileInfo i = itr.fileInfo();
            QString p = i.absoluteFilePath();
            
            if(i.completeSuffix() == "qml" || i.completeSuffix() == "ui.qml") {
                qDebug() << "added:" << p;
                w.addPath(p);
            }
        }
    }
    
    int r = 0;
    {
        QSharedPointer<ClientMessagingController> controller(new ClientMessagingController);
        
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("comms", controller.data());

        // Listens to events from the message bus and updates an in-memory
        // JSON model structure that's exposed to QML via pixie dust.
        DeviceModel model(controller, engine.rootContext());

        QObject::connect(&w, &QFileSystemWatcher::fileChanged, [&engine](QString p) {
            qDebug() << "reloading! this changed:" <<  p;
            engine.load(QUrl("./main.qml"));
        });
        
        QObject::connect(&engine, &QQmlApplicationEngine::warnings, [=](const QList<QQmlError> &warnings) {
            Q_FOREACH(const QQmlError& e, warnings) {
                qDebug() << "warning: " << e.toString();
            }
        });
        
        if(watch) {
            engine.setBaseUrl(QUrl::fromLocalFile(ichargerPath));
            engine.clearComponentCache();
            QUrl tmp("./main.qml");
            engine.load(tmp);
        } else
            engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        controller->init(pub_port, msg_port, data_dir);
        
        r = app.exec();
    }
    
    return r;
}

