#include "inverted.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

Inverted::Inverted() {
    this->description.type = "inverted";
    this->description.category = "Simple color";
    this->description.name = "Inverted";
    this->description.explanation = "Invert the colors in the image.";
    this->description.tooltip = "Invert the colors.";
}

Distortion* Inverted::cloneFromDescription(DistortionDescription description) const {
    return new Inverted(*this);
}

QString Inverted::stringOfInternalValues() const {
    return "";
}

void Inverted::distort(cv::Mat& mat) const{
    mat.forEach<cv::Vec4b>([](auto& pixel, auto) {
        pixel[0] = 255 - pixel[0];
        pixel[1] = 255 - pixel[1];
        pixel[2] = 255 - pixel[2];
    });
}
