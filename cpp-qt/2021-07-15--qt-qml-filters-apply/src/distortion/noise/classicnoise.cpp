#include "classicnoise.h"
#include "noise_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::noise {
    ClassicNoise::ClassicNoise() {
        this->description.type = "classicnoise";
        this->description.category = "Noise";
        this->description.name = "ClassicNoise";
        this->description.explanation = "Generating regular noise.\n"
                                        "The M and SIGMA variables are responsible for the color of the noise. Range 0-255.\n"
                                        "M is responsible for lightening the color.\n"
                                        "SIGMA is responsible for the strength of the color change.\n"
                                        "The remaining variables for the amount of the noise. Range 0-1.\n";
        this->description.tooltip = "Old tv effect.";
        this->description.arguments = msigmapMinpMaxArguments();
    }
    Distortion* ClassicNoise::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new ClassicNoise(*this);
        clone->m =
          description.arguments["m"].toObject()["value"].toDouble();
        clone->sigma =
          description.arguments["sigma"].toObject()["value"].toDouble();
        clone->powerMin =
          description.arguments["powerMin"].toObject()["value"].toDouble();
        clone->powerMax =
          description.arguments["powerMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString ClassicNoise::stringOfInternalValues() const {
        return QString("m: %0; sigma: %1; powerMin: %2; powerMax: %3")
          .arg(this->m)
          .arg(this->sigma)
          .arg(this->powerMin)
          .arg(this->powerMax);
    }
    void ClassicNoise::distort(cv::Mat& image) const {
        cv::Mat gaussian_noise = cv::Mat::zeros (image.rows, image.cols, CV_8UC4);
        cv::randn(gaussian_noise, m, sigma); //mean and variance
        double p = randomReal(powerMin, powerMax);
        image += gaussian_noise*p;

    }
}
