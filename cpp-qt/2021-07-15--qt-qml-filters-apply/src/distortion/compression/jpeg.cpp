#include "jpeg.h"
#include "distortion/distortion_common.h"

namespace distortion::compression {
    Jpeg::Jpeg() {
        this->description.type = "jpeg";
        this->description.category = "Compression";
        this->description.name = "Jpeg Compression";
        this->description.explanation = "Photo compression simulation to jpeg.\n"
                                        "The variable takes a value from 0 to 100. The lower the value, the worse the image quality. ";
        this->description.tooltip = "Jpeg Compression.";
        this->description.arguments["qualityMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Quality Min" },
                       { "value", 0 },
                       { "min", 0 },
                       { "max", 100 } };
        this->description.arguments["qualityMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Quality Max" },
                       { "value", 100 },
                       { "min", 0 },
                       { "max", 100 } };
    }
    Distortion* Jpeg::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Jpeg(*this);
        clone->qualityMin =
          description.arguments["qualityMin"].toObject()["value"].toInt();
        clone->qualityMax =
          description.arguments["qualityMax"].toObject()["value"].toInt();
        return clone;
    }
    QString Jpeg::stringOfInternalValues() const {
        return QString("qualityMin: %0; qualityMax: %1")
          .arg(this->qualityMin)
          .arg(this->qualityMax);
    }
    void Jpeg::distort(cv::Mat& image) const {
        int quality = randomInt(this->qualityMin, this->qualityMax);

        Q_ASSERT(quality >= 0);
        Q_ASSERT(quality <= 100);

        // https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#ga461f9ac09887e47797a54567df3b8b63
        // https://stackoverflow.com/questions/40768621/python-opencv-jpeg-compression-in-memory
        // https://stackoverflow.com/questions/41637438/opencv-imencode-buffer-exception

        cv::cvtColor(image, image, cv::COLOR_RGBA2BGRA);

        std::vector<uchar> buf;
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(quality);
        cv::imencode(".jpeg", image, buf, params);

        cv::imdecode(buf, 1, &image);
        cv::cvtColor(image, image, cv::COLOR_BGRA2RGBA);
    }
}
