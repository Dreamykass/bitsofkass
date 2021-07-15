#include "nored.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

NoRed::NoRed() {
    this->description.type = "nored";
    this->description.category = "Simple color";
    this->description.name = "NoRed";
    this->description.explanation = "Remove red color from the picture.";
    this->description.tooltip = "Remove red.";
}

Distortion* NoRed::cloneFromDescription(DistortionDescription description) const {
    return new NoRed(*this);
}

QString NoRed::stringOfInternalValues() const {
    return "";
}

void NoRed::distort(cv::Mat& mat) const{
    mat.forEach<cv::Vec4b>(
      [](auto& pixel, auto) { pixel[0] = 0; });
}
