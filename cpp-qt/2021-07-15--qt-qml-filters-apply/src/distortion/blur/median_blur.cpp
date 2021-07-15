#include "median_blur.h"
#include "distortion/distortion_common.h"

using namespace distortion::blur;

MedianBlur::MedianBlur() {
    this->description.type = "medianBlur";
    this->description.category = "Blur";
    this->description.name = "Median Blur";
    this->description.explanation = "The main idea of the median filter is to run through the signal entry by entry,\n"
                                    "replacing each entry with the median of neighboring entries.\n"
                                    "Variable range from 1 to 99. The variable is responsible for the number of pixels in the median.";
    this->description.tooltip = "Median Blur";

    this->description.arguments["kMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kMin" },
                   { "value", 1 },
                   { "min", 1 },
                   { "max", 99 } };
    this->description.arguments["kMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kMax" },
                   { "value", 21 },
                   { "min", 1 },
                   { "max", 99 } };
}

Distortion* MedianBlur::cloneFromDescription(DistortionDescription description) const {
    auto* clone = new MedianBlur(*this);
    clone->kMin =
      description.arguments["kMin"].toObject()["value"].toInt();
    clone->kMax =
      description.arguments["kMax"].toObject()["value"].toInt();
    return clone;
}

QString MedianBlur::stringOfInternalValues() const {
    return QString("kMin: %0; kMax: %1")
      .arg(this->kMin)
      .arg(this->kMax);
}

void MedianBlur::distort(cv::Mat &image) const{
    qDebug()<<"blurMedian function start";
    int kSize = distortion::randomInt(kMin, kMax);
    if(kSize%2==0){
        kSize++;
    }
    cv::medianBlur(image, image, kSize); // max 301
}
