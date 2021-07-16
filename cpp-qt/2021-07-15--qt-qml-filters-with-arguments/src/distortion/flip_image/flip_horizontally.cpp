#include "flip_horizontally.h"
#include "distortion/distortion_common.h"

using namespace distortion::flip_image;

FlipHorizontally::FlipHorizontally(){
    this->description.type = "flipHorizontally";
    this->description.category = "Flip image";
    this->description.name = "Flip Horizontally";
    this->description.explanation = "This function can flip image horizontally";
    this->description.tooltip = "Flip image horizontally";
}

Distortion* FlipHorizontally::cloneFromDescription(DistortionDescription) const {
    return new FlipHorizontally(*this);
}

QString FlipHorizontally::stringOfInternalValues() const { return ""; };

void FlipHorizontally::distort(cv::Mat& img) const {
    qDebug()<<"Flip an image Horizontally";
    cv::flip(img, img, 1);
}
