#ifndef HORIZONTALDROPPIXELS_H
#define HORIZONTALDROPPIXELS_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::pixel {
    class HorizontalDropPixels : public Distortion {
      public:
        HorizontalDropPixels();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double stepDeleteMin = -9999;
        double stepDeleteMax = -9999;
    };
}
#endif // HORIZONTALDROPPIXELS_H
