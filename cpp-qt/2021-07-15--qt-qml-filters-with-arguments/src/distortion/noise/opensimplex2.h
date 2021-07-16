#ifndef OPENSIMPLEX2_H
#define OPENSIMPLEX2_H

#include "distortion.h"
#include "opencv2/opencv.hpp"
#include "dep/FastNoiseLite.h"

namespace distortion::noise {
    class OpenSimplex2 : public Distortion {
      public:
        OpenSimplex2();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double offsetMin = -9999;
        double offsetMax = -9999;
    };
}
#endif // OPENSIMPLEX2_H
