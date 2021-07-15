#ifndef CANNY_H
#define CANNY_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::edge_detection {
class Canny : public Distortion {
  public:
    Canny();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
  private:
    int tMin = -9999;
    int tMax = -9999;
};
}

#endif // CANNY_H
