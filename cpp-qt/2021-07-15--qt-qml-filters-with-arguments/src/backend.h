#ifndef BACKEND_H
#define BACKEND_H

#include "distortion.h"
#include "image_provider.h"
#include <QJsonArray>
#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(ImageProvider *imageProvider, QObject *parent = nullptr);

public slots:
    QJsonArray getDistortionDescriptions();
    void loadImage(const QString &filename);
    void distort(const QJsonArray &descsJson);

private:
    ImageProvider *imageProvider;
    QMap<QString, QSharedPointer<const Distortion>> allDefaultDistortions;
};

#endif // BACKEND_H
