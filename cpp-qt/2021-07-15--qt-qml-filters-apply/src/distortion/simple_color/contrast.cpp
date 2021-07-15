#include "contrast.h"
#include "distortion/distortion_common.h"

using namespace distortion::simple_color;

Contrast::Contrast() {
    this->description.type = "contrast";
    this->description.category = "Simple color";
    this->description.name = "Contrast";
    this->description.explanation = "In visual perception of the real world, contrast is determined by the difference in the color and brightness of the object.\n"
                                    "Variable range from 1 to 3.";
    this->description.tooltip = "Contrast tooltip";

    this->description.arguments["betaMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "betaMin" },
                   { "value", 1 },
                   { "min", 1 },
                   { "max", 3 } };
    this->description.arguments["betaMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "betaMax" },
                   { "value", 1 },
                   { "min", 1 },
                   { "max", 3 } };
}

Distortion* Contrast::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new Contrast(*this);
    clone->betaMin =
      description.arguments["betaMin"].toObject()["value"].toInt();
    clone->betaMax =
      description.arguments["betaMax"].toObject()["value"].toInt();
    return clone;
}

QString Contrast::stringOfInternalValues() const {
    return QString("betaMin: %0; betaMax: %1")
      .arg(this->betaMin)
      .arg(this->betaMax);
}

void Contrast::distort(cv::Mat& img) const{

    //alpha [1.0-3.0]
    if(betaMin>=0 && betaMin<=3.0){
        if(betaMax>=0 && betaMax<=3.0){
            double alpha = distortion::randomReal(betaMin, betaMax);
            int beta = 0;  //simple brightness color
            img.convertTo(img, -1, alpha, beta);
        }else{
            qDebug()<< "incorrect betaMax value. Beta should be a value in the range 0-100";
            return;
        }
    }else{
        qDebug()<< "incorrect betaMin value. Beta should be a value in the range 0-100";
        return;
    }
}
