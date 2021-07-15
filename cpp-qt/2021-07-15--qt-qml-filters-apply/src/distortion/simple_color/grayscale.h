#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class Grayscale : public Distortion {
  public:
    Grayscale();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
};
}

#endif // GRAYSCALE_H
