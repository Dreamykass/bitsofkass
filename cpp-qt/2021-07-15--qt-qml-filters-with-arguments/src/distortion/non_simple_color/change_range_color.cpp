#include "change_range_color.h"
#include "distortion/distortion_common.h"

using namespace distortion::non_simple_color;

ChangeRangeColor::ChangeRangeColor() {
    this->description.type = "changerangecolor";
    this->description.category = "Non Simple Color";
    this->description.name = "ChangeRangeColor";
    this->description.explanation = "Change the color range to a different color.\n"
                                    "In the variables you enter the color range and the color you want to get in RGB. ";
    this->description.tooltip = "Change the color range.";
    this->description.arguments = changeRangeColorArguments();
}

Distortion* ChangeRangeColor::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new ChangeRangeColor(*this);
    clone->rMin =
      description.arguments["rMin"].toObject()["value"].toDouble();
    clone->rMax =
      description.arguments["rMax"].toObject()["value"].toDouble();
    clone->gMin =
      description.arguments["gMin"].toObject()["value"].toDouble();
    clone->gMax =
      description.arguments["gMax"].toObject()["value"].toDouble();
    clone->bMin =
      description.arguments["bMin"].toObject()["value"].toDouble();
    clone->bMax =
      description.arguments["bMax"].toObject()["value"].toDouble();
    clone->rMinFinal =
      description.arguments["rMinFinal"].toObject()["value"].toDouble();
    clone->rMaxFinal =
      description.arguments["rMaxFinal"].toObject()["value"].toDouble();
    clone->gMinFinal =
      description.arguments["gMinFinal"].toObject()["value"].toDouble();
    clone->gMaxFinal =
      description.arguments["gMaxFinal"].toObject()["value"].toDouble();
    clone->bMinFinal =
      description.arguments["bMinFinal"].toObject()["value"].toDouble();
    clone->bMaxFinal =
      description.arguments["bMaxFinal"].toObject()["value"].toDouble();
    return clone;
}

QString ChangeRangeColor::stringOfInternalValues() const {
    return QString("rMin: %0; rMax: %1, gMin: %2; gMax: %3, bMin: %4; bMax: %5, rMinFinal: %6; rMaxFinal: %7, gMinFinal: %8; gMaxFinal: %9, bMinFinal: %10; bMaxFinal: %11")
      .arg(this->rMin)
      .arg(this->rMax)
      .arg(this->gMin)
      .arg(this->gMax)
      .arg(this->bMin)
      .arg(this->bMax)
      .arg(this->rMinFinal)
      .arg(this->rMaxFinal)
      .arg(this->gMinFinal)
      .arg(this->gMaxFinal)
      .arg(this->bMinFinal)
      .arg(this->bMaxFinal);
}

void ChangeRangeColor::distort(cv::Mat& image) const {
    int fR, sR, fG, sG, fB, sB;
        fR=rMin;
        sR=rMax;
        fG=gMin;
        sG=gMax;
        fB=bMin;
        sB=bMax;
    if(randomInt(0,1)){
        fR = randomInt(rMin, rMax);
    } else{
        sR = randomInt(rMin, rMax);
    }
    if(randomInt(0,1)){
        fG = randomInt(gMin, gMax);
    }else{
        sG = randomInt(gMin, gMax);
    }
    if(randomInt(0,1)){
        fB = randomInt(bMin, bMax);
    }else{
        sB = randomInt(bMin, bMax);
    }

    int r = randomInt(rMinFinal, rMaxFinal);
    int g = randomInt(gMinFinal, gMaxFinal);
    int b = randomInt(bMinFinal, bMaxFinal);

    image.forEach<cv::Vec4b>(
      [fR, sR, fG, sG, fB, sB, r, g, b](auto& pixel, auto) {
       if(pixel[0]>=fR && pixel[1]>=fG && pixel[2]>=fB && pixel[0]<=sR && pixel[1]<=sG && pixel[2]<=sB){
       pixel[0] = r;
       pixel[1] = g;
       pixel[2] = b;
      }
    });
}

QJsonObject ChangeRangeColor::changeRangeColorArguments() {
    QJsonObject json;
    json["rMin"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "From Red Min" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["rMax"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "From Red Max" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["gMin"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "From Green Min" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["gMax"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "From Green Max" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["bMin"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "From Blue Min" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["bMax"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "From Blue Max" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["rMinFinal"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "To Red Min" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["rMaxFinal"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "To Red Max" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["gMinFinal"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "To Green Min" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["gMaxFinal"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "To Green Max" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["bMinFinal"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "To Blue Min" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    json["bMaxFinal"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "To Blue Max" },
                                   { "value", 40 },
                                   { "min", 0 },
                                   { "max", 255 } };
    return json;
}
