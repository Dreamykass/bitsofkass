#ifndef FLIP_VERTICALLY_H
#define FLIP_VERTICALLY_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::flip_image {
class FlipVertically : public Distortion {
  public:
    FlipVertically();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
};
}

#endif // FLIP_VERTICALLY_H
