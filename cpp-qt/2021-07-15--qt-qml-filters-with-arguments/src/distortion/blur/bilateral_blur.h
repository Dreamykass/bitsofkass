#ifndef BILATERALBLUR_H
#define BILATERALBLUR_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::blur {
class BilateralBlur : public Distortion {
  public:
    BilateralBlur();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    int dMin = -9999;
    int dMax = -9999;
    int sigmaColorMin = -9999;
    int sigmaColorMax = -9999;
    int sigmaSpaceMin = -9999;
    int sigmaSpaceMax = -9999;
};
}

#endif // BILATERALBLUR_H
