#include "flip_vertically.h"
#include "distortion/distortion_common.h"

using namespace distortion::flip_image;

FlipVertically::FlipVertically(){
    this->description.type = "flipVertically";
    this->description.category = "Flip image";
    this->description.name = "Flip Vertically";
    this->description.explanation = "This function can flip image vertically";
    this->description.tooltip = "Flip image vertically";
}

Distortion* FlipVertically::cloneFromDescription(DistortionDescription) const {
    return new FlipVertically(*this);
}

QString FlipVertically::stringOfInternalValues() const { return ""; };

void FlipVertically::distort(cv::Mat& img) const {
    qDebug()<<"Flip an image Vertically";
    cv::flip(img, img, 0);
}
