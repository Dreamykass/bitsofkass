#include "pixelatev2.h"
#include "distortion/distortion_common.h"

namespace distortion::pixel {
    Pixelatev2::Pixelatev2() {
        this->description.type = "pixelatev2";
        this->description.category = "Pixel";
        this->description.name = "Pixelatev2";
        this->description.explanation = "Pixelate with implemented blur.\n"
                                        "Variable range from 0 to 1. You divide the pixel size by the entered number.";
        this->description.tooltip = "Pixelate with blur.";
        this->description.arguments["scaleMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Scale Min" },
                       { "value", 0.1 },
                       { "min", 0 },
                       { "max", 1 } };
        this->description.arguments["scaleMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Scale Max" },
                       { "value", 0.1 },
                       { "min", 0 },
                       { "max", 1 } };
    }
    Distortion* Pixelatev2::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Pixelatev2(*this);
        clone->scaleMin =
          description.arguments["scaleMin"].toObject()["value"].toDouble();
        clone->scaleMax =
          description.arguments["scaleMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString Pixelatev2::stringOfInternalValues() const {
        return QString("scaleMin: %0; scaleMax: %1")
          .arg(this->scaleMin)
          .arg(this->scaleMax);
    }
    void Pixelatev2::distort(cv::Mat& image) const {
        double s = randomReal(scaleMin, scaleMax);
        int c = image.cols;
        int r = image.rows;
        cv::resize(image, image, cv::Size(), s, s);
        cv::resize(image, image, cv::Size(c, r), 0, 0);
    }
}
