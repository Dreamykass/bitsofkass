#ifndef CROPPING_H
#define CROPPING_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::transformation{
class Cropping : public Distortion{
public:
    Cropping();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

private:
    float leftEdgeDistMinPercent = -9999;
    float rightEdgeDistMinPercent=-9999;
    float topEdgeDistMinPercent=-9999;
    float bottomEdgeDistMinPercent=-9999;
    float leftEdgeDistMaxPercent = -9999;
    float rightEdgeDistMaxPercent=-9999;
    float topEdgeDistMaxPercent=-9999;
    float bottomEdgeDistMaxPercent=-9999;
};
}
#endif // CROPPING_H
