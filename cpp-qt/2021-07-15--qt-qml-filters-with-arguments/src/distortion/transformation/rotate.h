#ifndef ROTATE_H
#define ROTATE_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::transformation{
class Rotate: public Distortion{
public:
   Rotate();
   Distortion* cloneFromDescription(DistortionDescription) const override;
   QString stringOfInternalValues() const override;
   void distort(cv::Mat&) const override;

private:
   float degreeMin = -9999;
   float degreeMax=-9999;
};
}
#endif // ROTATE_H
