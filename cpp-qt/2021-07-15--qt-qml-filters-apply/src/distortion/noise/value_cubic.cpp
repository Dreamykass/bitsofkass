#include "value_cubic.h"
#include "noise_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::noise {
    ValueCubic::ValueCubic() {
        this->description.type = "valuecubic";
        this->description.category = "Noise";
        this->description.name = "ValueCubic";
        this->description.explanation = "Cubic noise is essentially scaled up white noise with cubic interpolation.\n"
                                        "Cubic interpolation ensures the result is smoothed enough to remove grid like artifacts.\n"
                                        "Variable range from 0 to 150. By increasing the variable, you increase the amount of noise.";
        this->description.tooltip = "ValueCubic noise";
        this->description.arguments = offsetMinMaxArguments();
    }
    Distortion* ValueCubic::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new ValueCubic(*this);
        clone->offsetMin =
          description.arguments["offsetMin"].toObject()["value"].toDouble();
        clone->offsetMax =
          description.arguments["offsetMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString ValueCubic::stringOfInternalValues() const {
        return QString("offsetMin: %0; offsetMax: %1")
          .arg(this->offsetMin)
          .arg(this->offsetMax);
    }
    void ValueCubic::distort(cv::Mat& image) const {
        int offset = randomInt(offsetMin, offsetMax);
        int ch = randomInt(0, 3);
        int cl = randomInt(0, 1);
        uchar channel = (uchar)ch;
        bool clamp = cl;
        channel = std::clamp(channel, (uchar)0, (uchar)3);

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);

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
