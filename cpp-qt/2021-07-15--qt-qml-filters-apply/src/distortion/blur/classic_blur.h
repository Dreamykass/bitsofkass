#ifndef CLASSICBLUR_H
#define CLASSICBLUR_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::blur{
class ClassicBlur : public Distortion {
  public:
    ClassicBlur();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    int wMin = -9999;
    int wMax = -9999;
    int hMin = -9999;
    int hMax = -9999;
};
}

#endif // CLASSICBLUR_H
