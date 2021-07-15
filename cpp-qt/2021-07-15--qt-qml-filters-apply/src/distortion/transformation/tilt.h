#ifndef TILT_H
#define TILT_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::transformation{
class Tilt: public Distortion{
public:
   Tilt();
   Distortion* cloneFromDescription(DistortionDescription) const override;
   QString stringOfInternalValues() const override;
   void distort(cv::Mat&) const override;

private:
   float verticalTiltMax = -9999;
   float verticalTiltMin=-9999;
   float horizontalTiltMax=-9999;
   float horizontalTiltMin=-9999;
};
}

#endif // TILT_H
