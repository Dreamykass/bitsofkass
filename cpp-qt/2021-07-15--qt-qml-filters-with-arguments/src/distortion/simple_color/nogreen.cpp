#include "nogreen.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

NoGreen::NoGreen() {
    this->description.type = "nogreen";
    this->description.category = "Simple color";
    this->description.name = "NoGreen";
    this->description.explanation = "Remove green color from the picture.";
    this->description.tooltip = "Remove green.";
}

Distortion* NoGreen::cloneFromDescription(DistortionDescription description) const {
    return new NoGreen(*this);
}

QString NoGreen::stringOfInternalValues() const {
    return "";
}

void NoGreen::distort(cv::Mat& mat) const{
    mat.forEach<cv::Vec4b>(
      [](auto& pixel, auto) { pixel[1] = 0; });
}
