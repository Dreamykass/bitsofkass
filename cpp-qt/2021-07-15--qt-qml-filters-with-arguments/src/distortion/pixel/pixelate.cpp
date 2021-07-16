#include "pixelate.h"
#include "distortion/distortion_common.h"

namespace distortion::pixel {
    Pixelate::Pixelate() {
        this->description.type = "pixelate";
        this->description.category = "Pixel";
        this->description.name = "Pixelate";
        this->description.explanation = "Pixelation happens when, instead of blending seamlessly, pixels become visible to the eye.\n"
                                        "Variable range from 0 to 1. You divide the pixel size by the entered number.";
        this->description.tooltip = "Make the pixels of an image bigger.";
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
    Distortion* Pixelate::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Pixelate(*this);
        clone->scaleMin =
          description.arguments["scaleMin"].toObject()["value"].toDouble();
        clone->scaleMax =
          description.arguments["scaleMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString Pixelate::stringOfInternalValues() const {
        return QString("scaleMin: %0; scaleMax: %1")
          .arg(this->scaleMin)
          .arg(this->scaleMax);
    }
    void Pixelate::distort(cv::Mat& image) const {
        double s = randomReal(scaleMin, scaleMax);
        int c = image.cols;
        int r = image.rows;
        cv::resize(image, image, cv::Size(), s, s);
        cv::resize(image, image, cv::Size(c, r), 0, 0, cv::INTER_NEAREST_EXACT);
    }
}
