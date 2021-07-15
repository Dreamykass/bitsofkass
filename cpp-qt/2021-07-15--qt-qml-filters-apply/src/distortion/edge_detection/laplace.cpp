#include "laplace.h"
#include "distortion/distortion_common.h"

using namespace distortion::edge_detection;

Laplace::Laplace(){
    this->description.type = "laplace";
    this->description.category = "Edge detection";
    this->description.name = "Laplace";
    this->description.explanation = "Edge detection.\n"
                                    "The function calculates the Laplacian of the source image by adding "
                                    "up the second x and y derivatives calculated using the Sobel operator.\n"
                                    "Before using this method, it is recommended that you use a gaussian filter.\n"
                                    "Kernel variables is responible for number of edges generated. Range 1-30.\n"
                                    "Delta variables is responible for lightening, consequently show more details. Range 0-100.";
    this->description.tooltip = "Before using this method, it is recommended that you use a gaussian filter.";

    this->description.arguments["sMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Kernel Min" },
                   { "value", 1 },
                   { "min", 1 },
                   { "max", 30 } };
    this->description.arguments["sMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Kernel Max" },
                   { "value", 5 },
                   { "min", 1 },
                   { "max", 30 } };
    this->description.arguments["dMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Delta Min" },
                   { "value", 1 },
                   { "min", 1 },
                   { "max", 100 } };
    this->description.arguments["dMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Delta Max" },
                   { "value", 15 },
                   { "min", 1 },
                   { "max", 100 } };
}

Distortion* Laplace::cloneFromDescription(
        DistortionDescription description) const {
    auto* clone = new Laplace(*this);
    clone->sMin =
      description.arguments["sMin"].toObject()["value"].toInt();
    clone->sMax =
      description.arguments["sMax"].toObject()["value"].toInt();
    clone->dMin =
      description.arguments["dMin"].toObject()["value"].toInt();
    clone->dMax =
      description.arguments["dMax"].toObject()["value"].toInt();
    return clone;
}

QString Laplace::stringOfInternalValues() const {
    return QString("sMin: %0; sMax: %1; dMin: %2; dMax: %3")
      .arg(this->sMin)
      .arg(this->sMax)
      .arg(this->dMin)
      .arg(this->dMax);
}

void Laplace::distort(cv::Mat& img) const {
    qDebug()<<"laplace start";
    int scale = distortion::randomInt(sMin, sMax);
    int delta = distortion::randomInt(dMin, dMax);
    cv::Mat grad;

    cv::cvtColor(img, img, cv::COLOR_RGBA2GRAY);
    cv::cvtColor(img, img, cv::COLOR_GRAY2RGBA);
    cv::Laplacian(img, grad, CV_16S, 3, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs(grad, img);
}
