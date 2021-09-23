#include <chrono>
#include <thread>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

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
    QObject *object = component.create();

    auto t = std::thread([=]() {
        auto start_time = std::chrono::steady_clock::now();

        while (true) {
            auto time_now = std::chrono::steady_clock::now();
            auto time_elapsed = time_now - start_time;
            auto hours = std::chrono::duration_cast<std::chrono::hours>(time_elapsed).count() % 24;
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(time_elapsed).count()
                           % 60;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count()
                           % 60;
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time_elapsed)
                                    .count()
                                % 1000;

            auto str = QString("%0:%1:%2.%3")
                           .arg(hours, 2)
                           .arg(minutes, 2)
                           .arg(seconds, 2)
                           .arg(milliseconds, 3);
            qDebug() << "c++:" << str;

            QMetaObject::invokeMethod(object, "updateTime", Q_ARG(QVariant, str));

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    });

    return app.exec();
}
