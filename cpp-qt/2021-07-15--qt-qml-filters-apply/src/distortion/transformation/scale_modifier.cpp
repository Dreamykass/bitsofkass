#include "scale_modifier.h"
#include "distortion/distortion_common.h"
#include "transformation_json_object.h"

namespace distortion::transformation{
ScaleModifier::ScaleModifier(){
    this->description.type = "Scale Modifier";
    this->description.category = "Modification";
    this->description.name = "Scale Modifier";
    this->description.explanation = "Zoom in or zoom out on the photo, by the given factor.";
    this->description.tooltip = "Scale image ";
    this->description.arguments["wMin"] =
            createQJsonObject<float>("double spin box","Degree width Min",0.1,2,1);
    this->description.arguments["wMax"] =
            createQJsonObject<float>("double spin box","Degree width Max",0.1,2,1);
    this->description.arguments["hMin"] =
            createQJsonObject<float>("double spin box","Degree height Min",0.1,2,1);
    this->description.arguments["hMax"] =
            createQJsonObject<float>("double spin box","Degree height Max",0.1,2,1);
}
//-----------------------------------------------------------------------------------
Distortion* ScaleModifier::cloneFromDescription(DistortionDescription description) const{
    auto* clone = new ScaleModifier(*this);
    clone->wMin =
            description.arguments["wMin"].toObject()["value"].toDouble();
    clone->wMax =
            description.arguments["wMax"].toObject()["value"].toDouble();
    clone->hMin =
            description.arguments["hMin"].toObject()["value"].toDouble();
    clone->hMax =
            description.arguments["hMax"].toObject()["value"].toDouble();
    return clone;
}
//-----------------------------------------------------------------------------------
QString ScaleModifier::stringOfInternalValues() const {
    return QString("leftEdgeDistMin: %0; rightEdgeDistMin: %1; topEdgeDistMin: %2; bottomEdgeDistMin: %3")
            .arg(this->wMin)
            .arg(this->wMax)
            .arg(this->hMin)
            .arg(this->hMax);
}
//-----------------------------------------------------------------------------------
void ScaleModifier::distort(cv::Mat &image) const{
    qDebug()<<"scaleModifier function start";
    double w = randomReal(wMin, wMax);
    double h = randomReal(hMin, hMax);
    cv::resize(image, image, cv::Size(), w, h);
}
}
