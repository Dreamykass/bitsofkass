
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "config.h"

Config loadConfig()
{
    Config c;

    if (!QFileInfo::exists("config.json"))
        qWarning("config.json does not exist");

    QFile file("config.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qWarning("!file.open");

    QJsonParseError jsonParseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();

    if (jsonParseError.error != QJsonParseError::NoError)
        qWarning() << "parse error: " << jsonParseError.errorString();

    c.url = jsonDoc["url"].toString();
    c.pathDatasetCreate = jsonDoc["pathDatasetCreate"].toString();
    c.authorization = jsonDoc["authorization"].toString();

    qDebug() << "url: " << c.url;
    qDebug() << "pathDatasetCreate: " << c.pathDatasetCreate;
    qDebug() << "authorization: " << c.authorization;

    return c;
}
