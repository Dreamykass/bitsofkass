#include "perlin.h"
#include "noise_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::noise {
    Perlin::Perlin() {
        this->description.type = "perlin";
        this->description.category = "Noise";
        this->description.name = "Perlin";
        this->description.explanation = "Perlin noise is a type of gradient noise.\n"
                                        "An implementation involves three steps:\n"
                                        "defining a grid of random gradient vectors\n"
                                        "computing the dot product between the gradient vectors and their offsets\n"
                                        "interpolation between these values.\n"
                                        "Variable range from 0 to 150. By increasing the variable, you increase the amount of noise.";
        this->description.tooltip = "Perlin noise";
        this->description.arguments = offsetMinMaxArguments();
    }
    Distortion* Perlin::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Perlin(*this);
        clone->offsetMin =
          description.arguments["offsetMin"].toObject()["value"].toDouble();
        clone->offsetMax =
          description.arguments["offsetMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString Perlin::stringOfInternalValues() const {
        return QString("offsetMin: %0; offsetMax: %1")
          .arg(this->offsetMin)
          .arg(this->offsetMax);
    }
    void Perlin::distort(cv::Mat& image) const {
        int offset = randomInt(offsetMin, offsetMax);
        int ch = randomInt(0, 3);
        int cl = randomInt(0, 1);
        uchar channel = (uchar)ch;
        bool clamp = cl;
        channel = std::clamp(channel, (uchar)0, (uchar)3);

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

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
