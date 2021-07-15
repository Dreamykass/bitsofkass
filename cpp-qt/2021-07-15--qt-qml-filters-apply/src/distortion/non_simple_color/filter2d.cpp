#include "filter2d.h"
#include "distortion/distortion_common.h"

using namespace distortion::non_simple_color;

Filter2D::Filter2D() {
    this->description.type = "filter2D";
    this->description.category = "Non Simple Color";
    this->description.name = "Filter2D";
    this->description.explanation = "Increases the effect of the light source.\n"
                                    "Kernel range 0-2";
    this->description.tooltip = "Increases the effect of the light source. ";

    this->description.arguments["kMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Kernel Min" },
                   { "value", 0.2 },
                   { "min", 0 },
                   { "max", 2 } };
    this->description.arguments["kMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Kernel Max" },
                   { "value", 0.8 },
                   { "min", 0 },
                   { "max", 2 } };
}

Distortion* Filter2D::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new Filter2D(*this);
    clone->kMin =
      description.arguments["kMin"].toObject()["value"].toDouble();
    clone->kMax =
      description.arguments["kMax"].toObject()["value"].toDouble();
    return clone;
}

QString Filter2D::stringOfInternalValues() const {
    return QString("kMin: %0; kMax: %1")
      .arg(this->kMin)
      .arg(this->kMax);
}

void Filter2D::distort(cv::Mat& image) const{
    qDebug()<< "Filter2D";
    double k = distortion::randomReal(kMin, kMax);
    double k2 = distortion::randomReal(kMin, kMax);
    double k3 = distortion::randomReal(kMin, kMax);
    double k4 = distortion::randomReal(kMin, kMax);
    cv::Mat_<float>kernel(2,2);
    kernel<<k,k2,k3,k4;
    cv::filter2D(image, image, -1, kernel, cv::Point(-1, -1));
}
