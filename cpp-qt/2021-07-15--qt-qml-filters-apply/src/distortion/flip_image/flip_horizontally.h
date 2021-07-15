#ifndef FLIP_HORIZONTALLY_H
#define FLIP_HORIZONTALLY_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::flip_image {
class FlipHorizontally : public Distortion {
  public:
    FlipHorizontally();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
};
}

#endif // FLIP_HORIZONTALLY_H
