#ifndef CHANGERANGECOLOR_H
#define CHANGERANGECOLOR_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::non_simple_color{
class ChangeRangeColor : public Distortion {
  public:
    ChangeRangeColor();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    QJsonObject changeRangeColorArguments();
    int rMin = -1;
    int rMax = -1;
    int gMin = -1;
    int gMax = -1;
    int bMin = -1;
    int bMax = -1;
    int rMinFinal = -1;
    int rMaxFinal = -1;
    int gMinFinal = -1;
    int gMaxFinal = -1;
    int bMinFinal = -1;
    int bMaxFinal = -1;
};
}
#endif // CHANGERANGECOLOR_H
