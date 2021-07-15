#ifndef MEDIANBLUR_H
#define MEDIANBLUR_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::blur{
class MedianBlur : public Distortion {
  public:
    MedianBlur();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    int kMin = -9999;
    int kMax = -9999;
};
}
#endif // MEDIANBLUR_H
