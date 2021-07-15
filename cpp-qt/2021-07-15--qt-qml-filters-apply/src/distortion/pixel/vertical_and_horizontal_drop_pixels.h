#ifndef VERTICALANDHORIZONTALDROPPIXELS_H
#define VERTICALANDHORIZONTALDROPPIXELS_H
#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::pixel {
    class VerticalAndHorizontalDropPixels : public Distortion {
      public:
        VerticalAndHorizontalDropPixels();
        Distortion* cloneFromDescription(DistortionDescription) const override;
        QString stringOfInternalValues() const;
        void distort(cv::Mat&) const override;
        void horizontalDrop(cv::Mat&) const;
        void verticalDrop(cv::Mat&) const;
        void bothDrop(cv::Mat&) const;

      private:
        double verticalRowStepDeleteMin = -9999;
        double verticalRowStepDeleteMax = -9999;
        double horizontalRowStepDeleteMin = -9999;
        double horizontalRowStepDeleteMax = -9999;
    };
}
#endif // VERTICALANDHORIZONTALDROPPIXELS_H
