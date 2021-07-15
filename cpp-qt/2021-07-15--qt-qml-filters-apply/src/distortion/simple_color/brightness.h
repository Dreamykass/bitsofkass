#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class Brightness : public Distortion {
  public:
    Brightness();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat& mat) const override;

  private:
    int betaMin = -9999;
    int betaMax = -9999;
};
}
#endif // BRIGHTNESS_H
