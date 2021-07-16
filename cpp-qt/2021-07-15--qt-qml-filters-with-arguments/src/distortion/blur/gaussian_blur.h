#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::blur
{
class GaussianBlur : public Distortion {
  public:
    GaussianBlur();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    int kMin = -9999;
    int kMax = -9999;
};
}

#endif // GAUSSIANBLUR_H
