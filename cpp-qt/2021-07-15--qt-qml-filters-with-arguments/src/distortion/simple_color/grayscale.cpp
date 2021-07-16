#include "grayscale.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

Grayscale::Grayscale()
{
    this->description.type = "grayscale";
    this->description.category = "Simple color";
    this->description.name = "Grayscale";
    this->description.explanation = "Change the photo to black and white.";
    this->description.tooltip = "Take an old picture.";
}

Distortion* Grayscale::cloneFromDescription(DistortionDescription description) const {
    return new Grayscale(*this);
}

QString Grayscale::stringOfInternalValues() const {
    return "";
}

void Grayscale::distort(cv::Mat& mat) const{
    cv::cvtColor(mat, mat, cv::COLOR_RGBA2GRAY);
    cv::cvtColor(mat, mat, cv::COLOR_GRAY2RGBA);
}
