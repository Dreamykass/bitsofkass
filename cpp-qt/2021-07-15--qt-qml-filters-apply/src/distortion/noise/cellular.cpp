#include "cellular.h"
#include "noise_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::noise {
    Cellular::Cellular() {
        this->description.type = "cellular";
        this->description.category = "Noise";
        this->description.name = "Cellular";
        this->description.explanation = "Cellular noise is random variability in quantities arising in cellular.\n"
                                        "Variable range from 0 to 150. By increasing the variable, you increase the amount of noise.";
        this->description.tooltip = "Cellular noise";
        this->description.arguments = offsetMinMaxArguments();
    }
    Distortion* Cellular::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Cellular(*this);
        clone->offsetMin =
          description.arguments["offsetMin"].toObject()["value"].toDouble();
        clone->offsetMax =
          description.arguments["offsetMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString Cellular::stringOfInternalValues() const {
        return QString("offsetMin: %0; offsetMax: %1")
          .arg(this->offsetMin)
          .arg(this->offsetMax);
    }
    void Cellular::distort(cv::Mat& image) const {
        int offset = randomInt(offsetMin, offsetMax);
        int ch = randomInt(0, 3);
        int cl = randomInt(0, 1);
        uchar channel = (uchar)ch;
        bool clamp = cl;
        channel = std::clamp(channel, (uchar)0, (uchar)3);

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

        image.forEach<cv::Vec4b>([&](auto& pixel, const int position[]) {
            double x = position[1] * 1.0 / image.cols * 255.0;
            double y = position[0] * 1.0 / image.rows * 255.0;

            double val = noise.GetNoise(x, y, (double)channel * randomReal(0, 20)) * offset;
            if (clamp) {
                pixel[channel] += std::clamp(val, 0.0, 255.0);
            } else {
                pixel[channel] += val;
            }
        });
    }
}
