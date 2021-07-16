#include "bilateral_blur.h"
#include "distortion/distortion_common.h"

using namespace distortion::blur;

BilateralBlur::BilateralBlur()
{
    this->description.type = "bilateralBlur";
    this->description.category = "Blur";
    this->description.name = "Bilateral Blur";
    this->description.explanation = "A bilateral filter is a non-linear, edge-preserving, and noise-reducing smoothing filter for images.\n"
                                    "It replaces the intensity of each pixel with a weighted average of intensity values from nearby pixels.\n"
                                    "The variable k is responsible for the strength of the blur. Range 0-5\n"
                                    "SigmaColor for color uniformity. Range 0-160\n"
                                    "SigmaSpace for the size of the space considered. Range 0-90\n"
                                    "THIS IS VERY TIME-consuming. ";
    this->description.tooltip = "Bilateral Blur";

    this->description.arguments["kMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "dMin" },
                   { "value", 0 },
                   { "min", 0 },
                   { "max", 5 } };
    this->description.arguments["kMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "dMax" },
                   { "value", 5 },
                   { "min", 0 },
                   { "max", 5 } };
    this->description.arguments["sigmaColorMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "sigmaColorMin" },
                   { "value", 0 },
                   { "min", 0 },
                   { "max", 160 } };
    this->description.arguments["sigmaColorMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "sigmaColorMax" },
                   { "value", 19 },
                   { "min", 0 },
                   { "max", 160 } };
    this->description.arguments["sigmaSpaceMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "sigmaSpaceMin" },
                   { "value", 0 },
                   { "min", 0 },
                   { "max", 90 } };
    this->description.arguments["sigmaSpaceMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "sigmaSpaceMax" },
                   { "value", 10 },
                   { "min", 0 },
                   { "max", 90 } };
}

Distortion* BilateralBlur::cloneFromDescription(
        DistortionDescription description) const{

    auto* clone = new BilateralBlur(*this);
    clone->dMin =
      description.arguments["dMin"].toObject()["value"].toInt();
    clone->dMax =
      description.arguments["dMax"].toObject()["value"].toInt();
    clone->sigmaColorMin =
      description.arguments["sigmaColorMin"].toObject()["value"].toInt();
    clone->sigmaColorMax =
      description.arguments["sigmaColorMax"].toObject()["value"].toInt();
    clone->sigmaSpaceMin =
      description.arguments["sigmaSpaceMin"].toObject()["value"].toInt();
    clone->sigmaSpaceMax =
      description.arguments["sigmaSpaceMax"].toObject()["value"].toInt();
    return clone;
}

QString BilateralBlur::stringOfInternalValues() const{
    return QString("Bilateral blur (dMin %0; dMax: %1, sigmaColorMin: "
                 "%2; sigmaColorMax: %3; "
                 "sigmaSpaceMin: %4; sigmaSpaceMax: %5)")
      .arg(this->dMin)
      .arg(this->dMax)
      .arg(this->sigmaColorMin)
      .arg(this->sigmaColorMax)
      .arg(this->sigmaSpaceMin)
      .arg(this->sigmaSpaceMax);
}

void BilateralBlur::distort(cv::Mat &image) const{
    qDebug()<<"blurBilateral function start";
    int d = distortion::randomInt(dMin, dMax);
    int sigmaColor = distortion::randomInt(sigmaColorMin, sigmaColorMax);
    int sigmaSpace = distortion::randomInt(sigmaSpaceMin, sigmaSpaceMax);
    cv::cvtColor(image, image, cv::COLOR_RGBA2RGB);
    cv::Mat tmp2 = image.clone();
    cv::bilateralFilter(tmp2, image, d, sigmaColor, sigmaSpace); // max 10 200 40
    cv::cvtColor(image, image, cv::COLOR_RGB2RGBA);
}
