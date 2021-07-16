#include "barrel.h"
#include "optical_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::optical {
    Barrel::Barrel() {
        this->description.type = "barrel";
        this->description.category = "Optical";
        this->description.name = "Barrel";
        this->description.explanation = "Barrel distortion effect, which corresponds to negative radial displacement.\n"
                                        "The range of the variable k is 1-1000. The entered value is divided by 10,000,000.";
        this->description.tooltip = "Tummy effect.";
        this->description.arguments = positionXYkXY();
    }
    Distortion* Barrel::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new Barrel(*this);
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
    QString Barrel::stringOfInternalValues() const {
        return QString("positionXMin: %0; positionXMax: %1, positionYMin: %2; positionYMax: %3, kXMin: %4; kXMax: %5, kYMin: %6; kYMax: %7")
          .arg(this->positionXMin)
          .arg(this->positionXMax)
          .arg(this->positionYMin)
          .arg(this->positionYMax)
          .arg(this->kXMin)
          .arg(this->kXMax)
          .arg(this->kYMin)
          .arg(this->kYMin);
    }
    void Barrel::distort(cv::Mat& image) const {
        int Cx = randomInt(positionXMin, positionXMax) * image.cols / 100;
        int Cy = randomInt(positionYMin, positionYMax) * image.rows / 100;
        double kx = randomReal(kXMin, kXMax) / 10000000;
        double ky = randomReal(kYMin, kYMin) / 10000000;
        cv::Mat mapx(image.rows, image.cols, CV_32FC1, cv::Scalar(0, 0, 0, 0));
        cv::Mat mapy(image.rows, image.cols, CV_32FC1, cv::Scalar(0, 0, 0, 0));

        int w= image.cols;
        int h= image.rows;

        float* pbuf = (float*)mapx.data;
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                float u= Cx+(x-Cx)*(1+kx*((x-Cx)*(x-Cx)+(y-Cy)*(y-Cy)));
                *pbuf = u;
                ++pbuf;
            }
        }

        pbuf = (float*)mapy.data;
        for (int y = 0;y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                *pbuf = Cy+(y-Cy)*(1+ky*((x-Cx)*(x-Cx)+(y-Cy)*(y-Cy)));
                ++pbuf;
            }
        }

        cv::Mat temp = image.clone();
        cv::remap( temp, image, mapx, mapy, 0);
    }
}
