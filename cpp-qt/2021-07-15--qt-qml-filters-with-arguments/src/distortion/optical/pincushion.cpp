#include "pincushion.h"
#include "optical_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::optical {
    Pincushion::Pincushion() {
        this->description.type = "pincushion";
        this->description.category = "Optical";
        this->description.name = "Pincushion";
        this->description.explanation = "Pincushion distortion effect, which corresponds to a positive radial displacement.\n"
                                        "The range of the variable k is 1-1000. The entered value is divided by 10,000,000.";
        this->description.tooltip = "Concave effect.";
        this->description.arguments = positionXYkXY();
    }
    Distortion* Pincushion::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Pincushion(*this);
        clone->positionXMin =
          description.arguments["positionXMin"].toObject()["value"].toDouble();
        clone->positionXMax =
          description.arguments["positionXMax"].toObject()["value"].toDouble();
        clone->positionYMin =
          description.arguments["positionYMin"].toObject()["value"].toDouble();
        clone->positionYMax =
          description.arguments["positionYMax"].toObject()["value"].toDouble();
        clone->kXMin =
          description.arguments["kXMin"].toObject()["value"].toDouble();
        clone->kXMax =
          description.arguments["kXMax"].toObject()["value"].toDouble();
        clone->kYMin =
          description.arguments["kYMin"].toObject()["value"].toDouble();
        clone->kYMax =
          description.arguments["kYMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString Pincushion::stringOfInternalValues() const {
        return QString("positionXMin: %0; positionXMax: %1, positionYMin: %2; positionYMax: %3, kXMin: %4; kXMax: %5, kYMin: %6; kYMin: %7")
          .arg(this->positionXMin)
          .arg(this->positionXMax)
          .arg(this->positionYMin)
          .arg(this->positionYMax)
          .arg(this->kXMin)
          .arg(this->kXMax)
          .arg(this->kYMin)
          .arg(this->kYMin);
    }
    void Pincushion::distort(cv::Mat& image) const {
        int Cx = randomInt(positionXMin, positionXMax) * image.cols / 100;
        int Cy = randomInt(positionYMin, positionYMax) * image.rows / 100;
        double kx = randomReal(kXMin, kXMax) / 10000000;
        double ky = randomReal(kYMin, kYMin) / 10000000;
        cv::Mat mapx(image.rows, image.cols, CV_32FC1, cv::Scalar(0, 0, 0, 0));
        cv::Mat mapy(image.rows, image.cols, CV_32FC1, cv::Scalar(0, 0, 0, 0));

        int w = image.cols;
        int h = image.rows;

        float* pbuf = (float*)mapx.data;
        for (int y = 0; y < h; y++) {
            int ty = y - Cy;
            for (int x = 0; x < w; x++) {
                int tx = x - Cx;
                int rt = tx * tx - ty * ty;
                *pbuf++ = ((tx * (1 + ky * rt) + Cx));
            }
        }

        pbuf = (float*)mapy.data;
        for (int y = 0; y < h; y++) {
            int ty = y - Cy;
            for (int x = 0; x < w; x++) {
                int tx = x - Cx;
                int rt = tx * tx - ty * ty;
                *pbuf++ = (ty * (1 - kx * rt) + Cy);
            }
        }

        cv::Mat temp = image.clone();
        cv::remap( temp, image, mapx, mapy, 0);

    }
}
