#include "backend.h"
#include "distortion.h"
#include <QJsonArray>
#include <QVariant>

Backend::Backend(ImageProvider *imageProvider, QObject *parent) : QObject(parent)
{
    this->imageProvider = imageProvider;
}

void Backend::loadImage(const QString &filename)
{
    this->imageProvider->loadImage(filename);
}

QJsonArray Backend::getDistortionDescriptions()
{
    QList<DistortionDescription> list;
    QJsonArray arr;

    {
        DistortionDescription d;
        d.type = "jpeg";
        d.category = "Compression";
        d.name = "Jpeg Compression";
        d.explanation = "Photo compression simulation to jpeg.\n"
                        "The variable takes a value from 0 to 100. The lower the value, the worse "
                        "the image quality. ";
        d.tooltip = "Jpeg Compression.";
        d.arguments["qualityMin"] = QJsonObject{{"type", "double spin box"},
                                                {"name", "Quality Min"},
                                                {"value", 0},
                                                {"min", 0},
                                                {"max", 100}};
        d.arguments["qualityMax"] = QJsonObject{{"type", "double spin box"},
                                                {"name", "Quality Max"},
                                                {"value", 100},
                                                {"min", 0},
                                                {"max", 100}};
        list.push_back(d);
    }
    {
        DistortionDescription d;
        d.type = "brightness";
        d.category = "Simple color";
        d.name = "Brightness";
        d.explanation = "Brighten the picture.\n"
                        "Variable range from 0 to 100.";
        d.tooltip = "Brighten the picture. ";

        d.arguments["betaMin"] = QJsonObject{{"type", "double spin box"},
                                             {"name", "betaMin"},
                                             {"value", 40},
                                             {"min", 0},
                                             {"max", 255}};
        d.arguments["betaMax"] = QJsonObject{{"type", "double spin box"},
                                             {"name", "betaMax"},
                                             {"value", 40},
                                             {"min", 0},
                                             {"max", 255}};
        list.push_back(d);
    }
    {
        DistortionDescription d;
        d.type = "contrast";
        d.category = "Simple color";
        d.name = "Contrast";
        d.explanation
            = "In visual perception of the real world, contrast is determined by the difference in "
              "the color and brightness of the object.\n"
              "Variable range from 1 to 3.";
        d.tooltip = "Contrast tooltip";

        d.arguments["betaMin"] = QJsonObject{{"type", "double spin box"},
                                             {"name", "betaMin"},
                                             {"value", 1},
                                             {"min", 1},
                                             {"max", 3}};
        d.arguments["betaMax"] = QJsonObject{{"type", "double spin box"},
                                             {"name", "betaMax"},
                                             {"value", 1},
                                             {"min", 1},
                                             {"max", 3}};

        list.push_back(d);
    }

    foreach (auto dd, list)
        arr.push_back(dd.toJsonObject());

    return arr;
}
