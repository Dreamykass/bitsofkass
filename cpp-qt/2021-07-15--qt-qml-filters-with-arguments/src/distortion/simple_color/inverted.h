#ifndef INVERTED_H
#define INVERTED_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::simple_color{
class Inverted : public Distortion {
  public:
    Inverted();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat& mat) const override;
};
}

#endif // INVERTED_H
