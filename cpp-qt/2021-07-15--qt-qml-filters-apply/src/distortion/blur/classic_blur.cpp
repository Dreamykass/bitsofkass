#include "classic_blur.h"
#include "distortion/distortion_common.h"

using namespace distortion::blur;

ClassicBlur::ClassicBlur()
{
        this->description.type = "classicBlur";
        this->description.category = "Blur";
        this->description.name = "Blur";
        this->description.explanation = "Classic image blur.\n"
                                        "You can adjust the blur strength horizontally and vertically.\n"
                                        "Variable range from 0 to 50.";
        this->description.tooltip = "Classic Blur";

        this->description.arguments["wMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Width min" },
                       { "value", 0 },
                       { "min", 0 },
                       { "max", 50 } };
        this->description.arguments["wMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Width max" },
                       { "value", 20 },
                       { "min", 0 },
                       { "max", 50 } };
        this->description.arguments["hMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Height min" },
                       { "value", 0 },
                       { "min", 0 },
                       { "max", 50 } };
        this->description.arguments["hMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Height max" },
                       { "value", 20 },
                       { "min", 0 },
                       { "max", 50 } };
}

Distortion* ClassicBlur::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new ClassicBlur(*this);
    clone->wMin =
      description.arguments["wMin"].toObject()["value"].toInt();
    clone->wMax =
      description.arguments["wMax"].toObject()["value"].toInt();
    clone->hMin =
      description.arguments["hMin"].toObject()["value"].toInt();
    clone->hMax =
      description.arguments["hMax"].toObject()["value"].toInt();
    return clone;
}

QString ClassicBlur::stringOfInternalValues() const{
    return QString("Blur (wMin %0; wMax: %1, hMin: %2; hMax: %3)")
      .arg(this->wMin)
      .arg(this->wMax)
      .arg(this->hMin)
      .arg(this->hMax);
}

void ClassicBlur::distort(cv::Mat &image) const{
    qDebug()<<"blur function start";
    int wSize = distortion::randomInt(wMin, wMax);
    if(wSize%2==0){
        wSize++;
    }
    int hSize = distortion::randomInt(hMin, hMax);
    if(hSize%2==0){
        hSize++;
    }
    cv::blur(image, image, cv::Size(wSize, hSize)); // max 500,500
}
