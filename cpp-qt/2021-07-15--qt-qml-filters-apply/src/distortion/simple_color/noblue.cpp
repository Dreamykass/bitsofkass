#include "noblue.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

NoBlue::NoBlue() {
    this->description.type = "noblue";
    this->description.category = "Simple color";
    this->description.name = "NoBlue";
    this->description.explanation = "Remove blue color from the picture .";
    this->description.tooltip = "Remove blue.";
}

Distortion* NoBlue::cloneFromDescription(DistortionDescription description) const {
    return new NoBlue(*this);
}

QString NoBlue::stringOfInternalValues() const { return ""; }

void NoBlue::distort(cv::Mat& mat) const{
    mat.forEach<cv::Vec4b>(
                [](auto& pixel, auto) { pixel[2] = 50; });
}

