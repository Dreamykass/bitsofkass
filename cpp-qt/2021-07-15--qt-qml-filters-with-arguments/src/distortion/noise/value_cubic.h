#ifndef VALUE_CUBIC_H
#define VALUE_CUBIC_H

#include "distortion.h"
#include "opencv2/opencv.hpp"
#include "dep/FastNoiseLite.h"

namespace distortion::noise {
    class ValueCubic : public Distortion {
      public:
        ValueCubic();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double offsetMin = -9999;
        double offsetMax = -9999;
    };
}
#endif // VALUE_CUBIC_H
