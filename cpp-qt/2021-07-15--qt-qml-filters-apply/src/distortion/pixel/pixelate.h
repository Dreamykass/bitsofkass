#ifndef PIXELATE_H
#define PIXELATE_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::pixel {
    class Pixelate : public Distortion {
      public:
        Pixelate();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double scaleMin = -9999;
        double scaleMax = -9999;
    };
}
#endif // PIXELATE_H
