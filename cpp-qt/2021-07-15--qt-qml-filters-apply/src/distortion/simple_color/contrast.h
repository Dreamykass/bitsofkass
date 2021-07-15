#ifndef CONTRAST_H
#define CONTRAST_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class Contrast : public Distortion {
  public:
    Contrast();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    int betaMin = -9999;
    int betaMax = -9999;
};
}
#endif // CONTRAST_H
