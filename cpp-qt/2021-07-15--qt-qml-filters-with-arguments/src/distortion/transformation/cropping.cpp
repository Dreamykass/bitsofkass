#include "cropping.h"
#include "transformation_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::transformation{
//============================================================================
Cropping::Cropping(){
    this->description.type = "Cropping";
    this->description.category = "Modification";
    this->description.name = "Cropping";
    this->description.explanation =
           "Select maximum and minimum edge distances to crop the image to a rectangle with a random edge distance from the original.\n"
            "The part outside the resulting rectangle will be cut off.";
    this->description.tooltip = "Crop image for minimum edge distances";

    this->description.arguments["leftEdgeDistMinPercent"] =
            createQJsonObject("double spin box", "Left Edge Distance Min",0,100,0);
    this->description.arguments["leftEdgeDistMaxPercent"] =
            createQJsonObject("double spin box", "Left Edge Distance Max",0,100,0);
    this->description.arguments["rightEdgeDistMinPercent"] =
            createQJsonObject("double spin box", "Right Edge Distance Min",0,100,0);
    this->description.arguments["rightEdgeDistMaxPercent"] =
            createQJsonObject("double spin box", "Right Edge Distance Max",0,100,0);
    this->description.arguments["topEdgeDistMinPercent"] =
            createQJsonObject("double spin box", "Top Edge Distance Min",0,100,0);
    this->description.arguments["topEdgeDistMaxPercent"] =
            createQJsonObject("double spin box", "Top Edge Distance Max",0,100,0);
    this->description.arguments["bottomEdgeDistMinPercent"] =
            createQJsonObject("double spin box", "Bottom Edge Distance Min",0,100,0);
    this->description.arguments["bottomEdgeDistMaxPercent"] =
            createQJsonObject("double spin box", "Bottom Edge Distance Max",0,100,0);
}
//-----------------------------------------------------------------------------------
Distortion* Cropping::cloneFromDescription(DistortionDescription description) const{
    auto* clone = new Cropping(*this);
    clone->leftEdgeDistMinPercent =
            description.arguments["leftEdgeDistMinPercent"].toObject()["value"].toDouble();
    clone->rightEdgeDistMinPercent =
            description.arguments["rightEdgeDistMinPercent"].toObject()["value"].toDouble();
    clone->topEdgeDistMinPercent =
            description.arguments["topEdgeDistMinPercent"].toObject()["value"].toDouble();
    clone->bottomEdgeDistMinPercent =
            description.arguments["bottomEdgeDistMinPercent"].toObject()["value"].toDouble();
    clone->leftEdgeDistMaxPercent =
            description.arguments["leftEdgeDistMaxPercent"].toObject()["value"].toDouble();
    clone->rightEdgeDistMaxPercent =
            description.arguments["rightEdgeDistMaxPercent"].toObject()["value"].toDouble();
    clone->topEdgeDistMaxPercent =
            description.arguments["topEdgeDistMaxPercent"].toObject()["value"].toDouble();
    clone->bottomEdgeDistMaxPercent =
            description.arguments["bottomEdgeDistMaxPercent"].toObject()["value"].toDouble();
    return clone;
}
//-----------------------------------------------------------------------------------
QString Cropping::stringOfInternalValues() const {
    return QString("leftEdgeDistMinPercent: %0; rightEdgeDistMinPercent: %1; "
                        "topEdgeDistMinPercent: %2; bottomEdgeDistMinPercent: %3; "
                        "leftEdgeDistMaxPercent: %4; rightEdgeDistMaxPercent: %5; "
                        "topEdgeDistMaxPercent: %6; bottomEdgeDistMaxPercent: %7")
            .arg(this->leftEdgeDistMinPercent)
            .arg(this->rightEdgeDistMinPercent)
            .arg(this->topEdgeDistMinPercent)
            .arg(this->bottomEdgeDistMinPercent)
            .arg(this->leftEdgeDistMaxPercent)
            .arg(this->rightEdgeDistMaxPercent)
            .arg(this->topEdgeDistMaxPercent)
            .arg(this->bottomEdgeDistMaxPercent);
}
//-----------------------------------------------------------------------------------
void Cropping::distort(cv::Mat &img) const{
    qDebug()<<"cropping distortion start\n";
    float width  = (float)img.cols;
    float height  = (float)img.rows;

    float leftEdgeDistMin = width*leftEdgeDistMinPercent/100;
    float rightEdgeDistMin= width*rightEdgeDistMinPercent/100;
    float topEdgeDistMin= height*topEdgeDistMinPercent/100;
    float bottomEdgeDistMin=height*bottomEdgeDistMinPercent/100;

    float leftEdgeDistMax = width*leftEdgeDistMaxPercent/100;
    float rightEdgeDistMax = width*rightEdgeDistMaxPercent/100;
    float topEdgeDistMax = height*topEdgeDistMaxPercent/100;
    float bottomEdgeDistMax =height*bottomEdgeDistMaxPercent/100;

    //percent
    float leftEdgeDist = randomReal(leftEdgeDistMin,leftEdgeDistMax);
    float rightEdgeDist = randomReal(rightEdgeDistMin,rightEdgeDistMax);
    float topEdgeDist =  randomReal(topEdgeDistMin,topEdgeDistMax);
    float bottomEdgeDist = randomReal(bottomEdgeDistMin,bottomEdgeDistMax);

    float x1,x2,y1,y2;

//        rightEdgeDist = width-rightEdgeDistMin;
//        bottomEdgeDist = height-bottomEdgeDistMin;

//        if(leftEdgeDistMin==rightEdgeDist ||
//                topEdgeDistMin==bottomEdgeDist)
//            return;


//        if(leftEdgeDistMin<=rightEdgeDist){
//            leftEdgeDist = leftEdgeDistMin;
//        }else{
//            leftEdgeDist = width - rightEdgeDistMin;
//            rightEdgeDist = leftEdgeDistMin;
//        }

//        if(topEdgeDistMin<=bottomEdgeDist){
//            topEdgeDist = topEdgeDistMin;
//        }else{
//            topEdgeDist = bottomEdgeDist;
//            bottomEdgeDist = topEdgeDistMin;
//        }

    x1 = leftEdgeDist;
    x2 = width-rightEdgeDist;
    y1 = topEdgeDist;
    y2 = height-bottomEdgeDist;

    if(x1>x2)
        std::swap(x1,x2);
    if(y1>y2)
        std::swap(y1,y2);

    // Setup a rectangle to define your region of interest
    cv::Rect roi(x1, y1, x2, y2);

    img = img(cv::Range(y1, y2), //horizontal
              cv::Range(x1, x2));//vertical
}
//===================================================================================
}
