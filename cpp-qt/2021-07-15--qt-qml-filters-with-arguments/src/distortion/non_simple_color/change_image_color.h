#ifndef CHANGEIMAGECOLOR_H
#define CHANGEIMAGECOLOR_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::non_simple_color{
class ChangeImageColor : public Distortion {
  public:
    ChangeImageColor();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;

  private:
    QJsonObject changeImageColorArguments();
    int rMin = -1;
    int rMax = -1;
    int gMin = -1;
    int gMax = -1;
    int bMin = -1;
    int bMax = -1;
};
}
#endif // CHANGEIMAGECOLOR_H
