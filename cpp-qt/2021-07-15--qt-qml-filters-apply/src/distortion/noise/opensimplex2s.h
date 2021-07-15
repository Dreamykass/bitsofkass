#ifndef OPENSIMPLEX2S_H
#define OPENSIMPLEX2S_H

#include "distortion.h"
#include "opencv2/opencv.hpp"
#include "dep/FastNoiseLite.h"

namespace distortion::noise {
    class OpenSimplex2S : public Distortion {
      public:
        OpenSimplex2S();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double offsetMin = -9999;
        double offsetMax = -9999;
    };
}
#endif // OPENSIMPLEX2S_H
