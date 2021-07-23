#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>

#include "config.h"

QHttpMultiPart *createParts()
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"witam name\""));

    QHttpPart descriptionPart;
    descriptionPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                              QVariant("form-data; description=\"siema description\""));

    return multiPart;
}

void send(const Config &config, QNetworkAccessManager &manager)
{
    auto *parts = createParts();

    QNetworkRequest request;
    request.setUrl(config.url + config.pathDatasetCreate);
    request.setRawHeader("Authorization", config.authorization.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "multipart/form-data; boundary=" + parts->boundary());

    manager.post(request, parts);

    QNetworkAccessManager::connect(&manager,
                                   &QNetworkAccessManager::finished,
                                   &manager,
                                   [](QNetworkReply *reply) {
                                       qDebug("finished");
                                       qDebug() << "reply->errorString(): " << reply->errorString();
                                       qDebug() << "reply->readAll(): " << reply->readAll();
                                       QCoreApplication::quit();
                                   });
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug("Hello");

    auto config = loadConfig();

    QNetworkAccessManager manager;
    send(config, manager);

    return a.exec();
}
