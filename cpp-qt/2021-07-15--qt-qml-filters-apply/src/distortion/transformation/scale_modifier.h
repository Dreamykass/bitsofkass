#ifndef SCALEMODIFIER_H
#define SCALEMODIFIER_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::transformation{
class ScaleModifier: public Distortion{
public:
   ScaleModifier();
   Distortion* cloneFromDescription(DistortionDescription) const override;
   QString stringOfInternalValues() const override;
   void distort(cv::Mat&) const override;

private:
   float wMin = -9999;
   float wMax=-9999;
   float hMin=-9999;
   float hMax=-9999;
};
}
#endif // SCALEMODIFIER_H
