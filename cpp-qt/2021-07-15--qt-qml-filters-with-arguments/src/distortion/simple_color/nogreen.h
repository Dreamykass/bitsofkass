#ifndef NOGREEN_H
#define NOGREEN_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class NoGreen : public Distortion {
  public:
    NoGreen();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat& mat) const override;
};
}

#endif // NOGREEN_H
