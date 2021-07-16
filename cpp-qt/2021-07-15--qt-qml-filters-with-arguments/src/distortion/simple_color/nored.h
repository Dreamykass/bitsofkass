#ifndef NORED_H
#define NORED_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class NoRed : public Distortion {
  public:
    NoRed();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat& mat) const override;
};
}

#endif // NORED_H
