#ifndef BARREL_H
#define BARREL_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::optical {
    class Barrel : public Distortion {
      public:
        Barrel();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        int positionXMin = 1;
        int positionXMax = 1;
        int positionYMin = 1;
        int positionYMax = 1;
        double kXMin = 0.000001;
        double kXMax = 0.000001;
        double kYMin = 0.000001;
        double kYMax = 0.000001;
    };
}
#endif // BARREL_H
