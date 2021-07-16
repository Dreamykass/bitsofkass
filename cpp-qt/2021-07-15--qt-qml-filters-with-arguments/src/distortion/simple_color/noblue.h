#ifndef NOBLUE_H
#define NOBLUE_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class NoBlue : public Distortion {
  public:
    NoBlue();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat& mat) const override;
};
}

#endif // NOBLUE_H
