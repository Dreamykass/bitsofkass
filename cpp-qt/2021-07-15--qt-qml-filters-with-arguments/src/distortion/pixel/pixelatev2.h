#ifndef PIXELATEV2_H
#define PIXELATEV2_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::pixel {
    class Pixelatev2 : public Distortion {
      public:
        Pixelatev2();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double scaleMin = -9999;
        double scaleMax = -9999;
    };
}
#endif // PIXELATEV2_H
