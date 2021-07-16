#ifndef FILTER2D_H
#define FILTER2D_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::non_simple_color{
class Filter2D : public Distortion {
  public:
    Filter2D();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    double kMin = -9999;
    double kMax = -9999;
};
}
#endif // FILTER2D_H
