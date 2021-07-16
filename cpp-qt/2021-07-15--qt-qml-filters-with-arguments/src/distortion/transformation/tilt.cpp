#include "tilt.h"
#include "distortion/distortion_common.h"
#include "transformation_json_object.h"

namespace distortion::transformation{
Tilt::Tilt(){
    this->description.type = "Tilt";
    this->description.category = "Modification";
    this->description.name = "Tilt";
    this->description.explanation =
            "Tilt the image by moving the vertical edges up or down and the horizontal edges to the left or right in opposite directions.";
    this->description.tooltip = "Tilt image";
    this->description.arguments["verticalTiltMax"] =
            createQJsonObject("double spin box", "Vertical Tilt Max",-100,100,0);
    this->description.arguments["verticalTiltMin"] =
            createQJsonObject("double spin box", "Vertical Tilt Min",-100,100,0);
    this->description.arguments["horizontalTiltMax"] =
            createQJsonObject("double spin box", "Horizontal Tilt Max",-100,100,0);
    this->description.arguments["horizontalTiltMin"] =
            createQJsonObject("double spin box", "Horizontal Tilt Min",-100,100,0);
}
//-----------------------------------------------------------------------------------
Distortion* Tilt::cloneFromDescription(DistortionDescription description) const{
    auto* clone = new Tilt(*this);
    clone->verticalTiltMax =
            description.arguments["verticalTiltMax"].toObject()["value"].toDouble();
    clone->verticalTiltMin =
            description.arguments["verticalTiltMin"].toObject()["value"].toDouble();
    clone->horizontalTiltMax =
            description.arguments["horizontalTiltMax"].toObject()["value"].toDouble();
    clone->horizontalTiltMin =
            description.arguments["horizontalTiltMin"].toObject()["value"].toDouble();
    return clone;
}
//-----------------------------------------------------------------------------------
QString Tilt::stringOfInternalValues() const {
    return QString("verticalTiltMax: %0; verticalTiltMin: %1; horizontalTiltMax: %2; horizontalTiltMin: %3")
            .arg(this->verticalTiltMax)
            .arg(this->verticalTiltMin)
            .arg(this->horizontalTiltMax)
            .arg(this->horizontalTiltMin);
}
//-----------------------------------------------------------------------------------
void Tilt::distort(cv::Mat &img) const{
    qDebug()<<"tilt function start";

    float w = img.cols;
    float h = img.rows;

    float verticalTilt = randomReal(w*verticalTiltMin/100, w*verticalTiltMax/100);
    float horizontalTilt = randomReal(h*horizontalTiltMin/100, h*horizontalTiltMax/100);

    qDebug()<<"vertical "<<verticalTilt<<"\nhorizontal "<<horizontalTilt;
    cv::Point2f src_p[4];
    cv::Point2f dst_p[4];

    float width = (float)img.cols;
    float height = (float)img.rows;

    float absoluteVerticalTilt = abs(verticalTilt);
    float absoluteHorizontalTilt = abs(horizontalTilt);

    float new_w = width + 2* absoluteVerticalTilt;
    float new_h = height + 2 * absoluteHorizontalTilt;

    // from points
    src_p[0] = cv::Point2f(0.0f, 0.0f);     //top left corner
    src_p[1] = cv::Point2f(width, 0.0f);    //top right corner
    src_p[2] = cv::Point2f(width, height);   //bottom right corner
    src_p[3] = cv::Point2f(0.0f, height);    //bottom left corner

    dst_p[0] = cv::Point2f(0.0f+verticalTilt+absoluteVerticalTilt, 0.0f-horizontalTilt+absoluteHorizontalTilt);
    dst_p[1] = cv::Point2f(width+verticalTilt+absoluteVerticalTilt, 0.0f+horizontalTilt+absoluteHorizontalTilt);
    dst_p[2] = cv::Point2f(width-verticalTilt+absoluteVerticalTilt, height+horizontalTilt+absoluteHorizontalTilt);
    dst_p[3] = cv::Point2f(0.0f-verticalTilt+absoluteVerticalTilt, height-horizontalTilt+absoluteHorizontalTilt);

    // create perspective transform matrix 3x3
    cv::Mat trans_M3x3 = cv::getPerspectiveTransform(src_p, dst_p);

    // perspective transform operation using transform matrix
    cv::warpPerspective(img, img, trans_M3x3, cv::Size(new_w, new_h), cv::INTER_LINEAR);
}
}
