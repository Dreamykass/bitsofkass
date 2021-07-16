#include "brightness.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

Brightness::Brightness()
{
        this->description.type = "brightness";
        this->description.category = "Simple color";
        this->description.name = "Brightness";
        this->description.explanation = "Brighten the picture.\n"
                                        "Variable range from 0 to 100.";
        this->description.tooltip = "Brighten the picture. ";

        this->description.arguments["betaMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "betaMin" },
                       { "value", 40 },
                       { "min", 0 },
                       { "max", 255 } };
        this->description.arguments["betaMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "betaMax" },
                       { "value", 40 },
                       { "min", 0 },
                       { "max", 255 } };
}

Distortion* Brightness::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new Brightness(*this);
    clone->betaMin =
      description.arguments["betaMin"].toObject()["value"].toInt();
    clone->betaMax =
      description.arguments["betaMax"].toObject()["value"].toInt();
    return clone;
}

QString Brightness::stringOfInternalValues() const {
    return QString("betaMin: %0; betaMax: %1")
      .arg(this->betaMin)
      .arg(this->betaMax);
}

void Brightness::distort(cv::Mat& img) const {
    // beta [(-100)-100]
    if (betaMin >= -100 && betaMin < 100) {
        if (betaMax > -100 && betaMax <= 100) {
            double alpha = 1.0; // simple contrast color
            int beta = randomInt(betaMin, betaMax);
            img.convertTo(img, -1, alpha, beta);
        } else {
            qDebug() << "incorrect betaMax value. Beta should be a value "
                        "in the range 0-100";
            return;
        }
    } else {
        qDebug() << "incorrect betaMin value. Beta should be a value in "
                    "the range 0-100";
        return;
    }
}
