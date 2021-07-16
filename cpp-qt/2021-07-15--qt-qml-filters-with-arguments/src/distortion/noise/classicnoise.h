#ifndef CLASSICNOISE_H
#define CLASSICNOISE_H

#include "distortion.h"
#include "opencv2/opencv.hpp"
#include "dep/FastNoiseLite.h"

namespace distortion::noise {
    class ClassicNoise : public Distortion {
      public:
        ClassicNoise();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        int m = -9999;
        int sigma = -9999;
        double powerMin = -9999;
        double powerMax = -9999;
    };
}
#endif // CLASSICNOISE_H
