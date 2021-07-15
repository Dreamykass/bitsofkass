#ifndef PERLIN_H
#define PERLIN_H

#include "distortion.h"
#include "opencv2/opencv.hpp"
#include "dep/FastNoiseLite.h"

namespace distortion::noise {
    class Perlin : public Distortion {
      public:
        Perlin();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double offsetMin = -9999;
        double offsetMax = -9999;
    };
}
#endif // PERLIN_H
