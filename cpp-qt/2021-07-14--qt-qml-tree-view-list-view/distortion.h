#ifndef DISTORTION_H
#define DISTORTION_H

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
};

#endif // DISTORTION_H
