#ifndef VERTICALDROPPIXELS_H
#define VERTICALDROPPIXELS_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::pixel {
    class VerticalDropPixels : public Distortion {
      public:
        VerticalDropPixels();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;

      private:
        double stepDeleteMin = -9999;
        double stepDeleteMax = -9999;
    };
}
#endif // VERTICALDROPPIXELS_H
