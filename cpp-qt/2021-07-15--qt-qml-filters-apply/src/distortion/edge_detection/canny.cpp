#include "canny.h"
#include "distortion/distortion_common.h"

using namespace distortion::edge_detection;

Canny::Canny(){
    this->description.type = "canny";
    this->description.category = "Edge detection";
    this->description.name = "Canny";
    this->description.explanation = "Edge detection.\n"
                                    "Any edges with intensity gradient more than Threshold Max are sure to be edges and those "
                                    "\nbelow Threshold Min are sure to be non-edges, so discarded. Those who lie between these \n"
                                    "two thresholds are classified edges or non-edges based on their connectivity. \n"
                                    "If they are connected to sure-edge pixels, they are considered to be part of edges. "
                                    "Otherwise, they are also discarded.\n"
                                    "Before using this method, it is recommended that you use a gaussian filter.\n"
                                    "Threshold variables is responible for number of edges generated. Range 1-100.";
    this->description.tooltip = "Before using this method, it is recommended that you use a gaussian filter.";

    this->description.arguments["tMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Threshold Min" },
                   { "value", 20 },
                   { "min", 1 },
                   { "max", 100 } };
    this->description.arguments["tMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Threshold Max" },
                   { "value", 50 },
                   { "min", 1 },
                   { "max", 100 } };
}

Distortion* Canny::cloneFromDescription(
        DistortionDescription description) const {
    auto* clone = new Canny(*this);
    clone->tMin =
      description.arguments["tMin"].toObject()["value"].toInt();
    clone->tMax =
      description.arguments["tMax"].toObject()["value"].toInt();
    return clone;
}

QString Canny::stringOfInternalValues() const {
    return QString("tMin: %0; tMax: %1")
      .arg(this->tMin)
      .arg(this->tMax);
}

void Canny::distort(cv::Mat& img) const {
    qDebug()<<"canny start";
    int lowThreshold = distortion::randomInt(tMin, tMax);
    const int ratio = 3;

    cv::cvtColor(img, img, cv::COLOR_RGBA2GRAY);
    cv::Canny(img, img, lowThreshold, lowThreshold * ratio, 3, false);
    cv::cvtColor(img, img, cv::COLOR_GRAY2RGBA);
}
