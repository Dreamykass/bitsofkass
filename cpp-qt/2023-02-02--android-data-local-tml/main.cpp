#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QtGlobal>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);

  qSetMessagePattern("[%{time h:mm:ss.zzz}] "
                     "[%{type}] [%{function}:%{line}] "
                     "%{if-category}[%{category}] %{endif}: %{message}");

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  {
    QDir dirToSaveFile{"/data/local/tmp/"};
    if (!dirToSaveFile.exists()) {
      qWarning()
          << "Directory /data/local/tmp/ is not existent on this device!";
    }
    dirToSaveFile.mkdir("oxy_firmware");
    bool folderExists = dirToSaveFile.cd("oxy_firmware");
    if (!folderExists) {
      qWarning() << "Couldn't create oxy_firmware folder!";
    }
    QString fileName = "oxy_firmware.zip";
    QString absFilePath = dirToSaveFile.absoluteFilePath(fileName);
  }

  {
    QFile data("/data/local/tmp/output.txt");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
      qDebug() << "data open ok";
      QTextStream out(&data);
      out << "Result: "
          << "ouch: " << 3.14 << 2.7;
      // writes "Result: 3.14      2.7       "
    } else {
      qDebug() << "data open bad";
    }
  }

  {
    QDir d{"/storage/emulated/0/Android/data/org.oxy"};
    qWarning() << "/storage/emulated: " << d.exists();
    foreach (auto x, d.entryList({"*"})) { qWarning() << x; }
  }

  {
    QFile data("/storage/emulated/0/Android/data/org.oxy/output.txt");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
      qDebug() << "data open ok";
      QTextStream out(&data);
      out << "Result: "
          << "ouch: " << 3.14 << 2.7;
      // writes "Result: 3.14      2.7       "
    } else {
      qDebug() << "data open bad";
    }
  }

  return app.exec();
}
