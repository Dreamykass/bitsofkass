#include "backend.h"
#include "device.h"
#include "device_bt.h"
#include "device_fake.h"
#include "state.h"
#include <QGuiApplication>
#include <QMetaObject>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtGlobal>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qSetMessagePattern("[%{type}] [%{function}:%{line}] "
                       "%{if-category}[%{category}] %{endif}: %{message}");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    // engine.load(url);
    QQmlComponent component(&engine, url);
    QObject *object = component.create();

    //    BluetoothDevice device;
    FakeDevice device;
    Backend backend(device, *object);
    engine.rootContext()->setContextProperty("backend", &backend);

    // device->backend connections
    {
        //QObject::connect(&device, &BluetoothDevice::foundPeripheralSig, &backend, &Backend::foundPeripheral);
        //QObject::connect(&device, &BluetoothDevice::connectedSig, &backend, &Backend::connected);

        QObject::connect(&device,
                         &FakeDevice::foundPeripheralSig,
                         &backend,
                         &Backend::foundPeripheral);
        QObject::connect(&device, &FakeDevice::connectedSig, &backend, &Backend::connected);
    }

    return app.exec();
}
