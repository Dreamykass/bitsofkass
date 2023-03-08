#include <QDebug>
#include <QDir>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtGlobal>

#include "backend.h"

QString getAbsFilePathToSaveFirmwareFile() {
  // put the zip in /data/local/tmp/oxy_firmware
  // TODO make this fun more secure, add android path handle!
  QDir dirToSaveFile = QDir().temp();
  dirToSaveFile.cd("data");
  dirToSaveFile.cd("local");
  dirToSaveFile.cd("tmp");
  dirToSaveFile.cd("oxy_firmware");
  QString fileName = "oxy_firmware.zip";
  QString absFilePath = dirToSaveFile.absoluteFilePath(fileName);
  return absFilePath;
}

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  qDebug() << "===============================";
  qDebug() << "===============================";
  qDebug() << "===============================";
  qDebug() << "===============================";
  qDebug() << "===============================";
  qDebug() << "===============================";
  qDebug() << "getAbsFilePathToSaveFirmwareFile() == "
           << getAbsFilePathToSaveFirmwareFile();

  auto backend = Backend{};
  engine.rootContext()->setContextProperty("Backend", &backend);

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
