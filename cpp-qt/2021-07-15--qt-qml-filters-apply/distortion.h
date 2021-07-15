#ifndef DISTORTION_H
#define DISTORTION_H

#include <opencv2/opencv.hpp>
#include <QJsonObject>
#include <QString>

struct DistortionDescription
{
public:
    QString type;

    QString category;

    QString name;

    QString explanation;

    QString tooltip;

    QJsonObject arguments;

    QJsonObject toJsonObject() const
    {
        return {
            {"type", type},
            {"category", category},
            {"name", name},
            {"explanation", explanation},
            {"tooltip", tooltip},
            {"arguments", arguments},
        };
    }

    static DistortionDescription fromJsonObject(const QJsonObject &json)
    {
        return {
            json["type"].toString(),
            json["category"].toString(),
            json["name"].toString(),
            json["explanation"].toString(),
            json["tooltip"].toString(),
            json["arguments"].toObject(),
        };
    }
};

class Distortion
{
public:
    virtual ~Distortion(){};

    virtual Distortion *cloneFromDescription(DistortionDescription description) const = 0;

    virtual QString stringOfInternalValues() const = 0;

    virtual void distort(cv::Mat &mat) const = 0;

    DistortionDescription description;
};

QMap<QString, QSharedPointer<const Distortion>> getAllDefaultDistortions();

#endif // DISTORTION_H
