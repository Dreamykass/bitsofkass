#include "change_image_color.h"
#include "distortion/distortion_common.h"

using namespace distortion::non_simple_color;

ChangeImageColor::ChangeImageColor() {
    this->description.type = "changeimagecolor";
    this->description.category = "Non Simple Color";
    this->description.name = "ChangeImageColor";
    this->description.explanation = "Dodaj lub usuń ze zdjęcia trochę barw.\n"
                                    "RGB format.";
    this->description.tooltip = "Change the color of the photo.";
    this->description.arguments = changeImageColorArguments();
}
Distortion* ChangeImageColor::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new ChangeImageColor(*this);
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
    return clone;
}
QString ChangeImageColor::stringOfInternalValues() const {
    return QString("rMin: %0; rMax: %1, gMin: %2; gMax: %3, bMin: %4; bMax: %5")
      .arg(this->rMin)
      .arg(this->rMax)
      .arg(this->gMin)
      .arg(this->gMax)
      .arg(this->bMin)
      .arg(this->bMax);
}
void ChangeImageColor::distort(cv::Mat& image) const {
    int r = randomInt(rMin, rMax);
    int g = randomInt(gMin, gMax);
    int b = randomInt(bMin, bMax);
    image.forEach<cv::Vec4b>(
      [r, g, b](auto& pixel, auto) {
       pixel[0] = pixel[0] + r;
       pixel[1] = pixel[1] + g;
       pixel[2] = pixel[2] + b;
    });
}

QJsonObject ChangeImageColor::changeImageColorArguments() {
    QJsonObject json;
    json["rMin"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "Add Red Min" },
                                   { "value", 40 },
                                   { "min", -256 },
                                   { "max", 256 } };
    json["rMax"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "Add Red Max" },
                                   { "value", 40 },
                                   { "min", -256 },
                                   { "max", 256 } };
    json["gMin"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "Add Green Min" },
                                   { "value", 40 },
                                   { "min", -256 },
                                   { "max", 256 } };
    json["gMax"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "Add Green Max" },
                                   { "value", 40 },
                                   { "min", -256 },
                                   { "max", 255 } };
    json["bMin"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "Add Blue Min" },
                                   { "value", 40 },
                                   { "min", -256 },
                                   { "max", 256 } };
    json["bMax"] = QJsonObject{ { "type", "double spin box" },
                                   { "name", "Add Blue Max" },
                                   { "value", 40 },
                                   { "min", -256 },
                                   { "max", 256 } };
    return json;
}
