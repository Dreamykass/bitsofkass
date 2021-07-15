#include "backend.h"
#include "distortion.h"
#include <QJsonArray>
#include <QVariant>

Backend::Backend(ImageProvider *imageProvider, QObject *parent) : QObject(parent)
{
    this->imageProvider = imageProvider;
    this->allDefaultDistortions = getAllDefaultDistortions();
}

void Backend::loadImage(const QString &filename)
{
    this->imageProvider->loadImage(filename);
}

void Backend::distort(const QJsonArray &descsJson)
{
    //    qDebug() << descsJson;

    QList<QSharedPointer<Distortion>> dists;

    foreach (const auto descJson, descsJson) {
        auto desc = DistortionDescription::fromJsonObject(descJson.toObject());
        qDebug() << desc.type;
        dists.push_back(QSharedPointer<Distortion>(
            this->allDefaultDistortions[desc.type]->cloneFromDescription(desc)));
    }

    this->imageProvider->distort(dists);
}

QJsonArray Backend::getDistortionDescriptions()
{
    QJsonArray arr;

    foreach (auto dd, this->allDefaultDistortions.values())
        arr.push_back(dd->description.toJsonObject());

    return arr;
}
