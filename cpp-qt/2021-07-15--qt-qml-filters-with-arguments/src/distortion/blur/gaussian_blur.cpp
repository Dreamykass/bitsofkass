#include "gaussian_blur.h"
#include "distortion/distortion_common.h"

using namespace distortion::blur;
GaussianBlur::GaussianBlur()
{
    this->description.type = "gaussianBlur";
    this->description.category = "Blur";
    this->description.name = "Gaussian Blur";
    this->description.explanation = "The visual effect of this blurring technique is a smooth blur\n"
                                    "resembling that of viewing the image through a translucent screen.\n"
                                    "Variable range from 0 to 20. By increasing the variable, you increase the strength of the blur.";
    this->description.tooltip = "Gaussian Blur";

    this->description.arguments["kMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kMin" },
                   { "value", 1 },
                   { "min", 0 },
                   { "max", 20 } };
    this->description.arguments["kMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kMax" },
                   { "value", 5 },
                   { "min", 0 },
                   { "max", 20 } };
}

Distortion* GaussianBlur::cloneFromDescription(DistortionDescription) const {
    auto* clone = new GaussianBlur(*this);
    clone->kMin =
      description.arguments["kMin"].toObject()["value"].toInt();
    clone->kMax =
      description.arguments["kMax"].toObject()["value"].toInt();
    return clone;
}

QString GaussianBlur::stringOfInternalValues() const {
    return QString("kMin: %0; kMax: %1")
      .arg(this->kMin)
      .arg(this->kMax);
}

void GaussianBlur::distort(cv::Mat &image) const{
    qDebug()<<"blurGaussian function start";
    int kSize = distortion::randomInt(kMin, kMax);
    if(kSize%2==0){
        kSize++;
    }
    cv::GaussianBlur(image, image, cv::Size(), kSize); // max 50
}
