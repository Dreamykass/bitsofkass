#ifndef LAPLACE_H
#define LAPLACE_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::edge_detection {
class Laplace : public Distortion {
  public:
    Laplace();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
  private:
    int sMin = -9999;
    int sMax = -9999;
    int dMin = -9999;
    int dMax = -9999;
};
}

#endif // LAPLACE_H
