#ifndef SOBEL_H
#define SOBEL_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::edge_detection {
class Sobel : public Distortion {
  public:
    Sobel();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
  private:
    int kMin = -9999;
    int kMax = -9999;
    int dMin = -9999;
    int dMax = -9999;
};
}

#endif // SOBEL_H
