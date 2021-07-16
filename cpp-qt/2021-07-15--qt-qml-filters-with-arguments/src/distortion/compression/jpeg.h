#ifndef JPEG_H
#define JPEG_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::compression {
    class Jpeg : public Distortion {
      public:
        Jpeg();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const override;
        void distort(cv::Mat&) const override;

      private:
        int qualityMin;
        int qualityMax;
    };
}

#endif // JPEG_H
