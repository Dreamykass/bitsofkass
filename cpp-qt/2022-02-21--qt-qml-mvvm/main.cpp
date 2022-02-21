#include "controller.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QtGlobal>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qSetMessagePattern("[%{time h:mm:ss.zzz}] "
                       "[%{type}] [%{function}:%{line}] "
                       "%{if-category}[%{category}] %{endif}: %{message}");

    QGuiApplication app(argc, argv);

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
    QObject *qml_main_window = component.create();

    Controller controller(qml_main_window);

    return app.exec();
}
