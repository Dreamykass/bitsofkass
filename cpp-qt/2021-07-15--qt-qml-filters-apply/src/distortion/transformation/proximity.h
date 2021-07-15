#ifndef PROXIMITY_H
#define PROXIMITY_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::transformation{
class Proximity: public Distortion{
public:
   Proximity();
   Distortion* cloneFromDescription(DistortionDescription) const override;
   QString stringOfInternalValues() const override;
   void distort(cv::Mat&) const override;

private:
   float percentMin = -9999;
   float percentMax=-9999;
};
}
#endif // PROXIMITY_H
