#include "proximity.h"
#include "transformation_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::transformation{
Proximity::Proximity(){
    this->description.type = "Proximity";
    this->description.category = "Modification";
    this->description.name = "Proximity";
    this->description.explanation =
            "Zoom in to the center of the image.\n"
            "The image dimensions remain the same."
            "0% - no zoom, 100% - max zoom.";
    this->description.tooltip = "Zoom in to the center of the image";
    this->description.arguments["percentMin"] =
            createQJsonObject("double spin box","Proximity Min",0,100,0);
    this->description.arguments["percentMax"] =
            createQJsonObject("double spin box","Proximity Max",0,100,0);
}
//-----------------------------------------------------------------------------------
Distortion* Proximity::cloneFromDescription(DistortionDescription description) const{
    auto* clone = new Proximity(*this);
    clone->percentMin =
            description.arguments["percentMin"].toObject()["value"].toDouble();
    clone->percentMax =
            description.arguments["percentMax"].toObject()["value"].toDouble();
    return clone;
}
//-----------------------------------------------------------------------------------
QString Proximity::stringOfInternalValues() const {
    return QString("percentMin: %0; percentMax: %1")
            .arg(this->percentMin)
            .arg(this->percentMax);
}
//-----------------------------------------------------------------------------------
void Proximity::distort(cv::Mat &img) const{
    qDebug()<<"proximity function start";
    int percentValue = randomInt(percentMin, percentMax);

    double percent = (double)percentValue/(double)100;

    cv::Point2f src_p[4];
    cv::Point2f dst_p[4];

    float width  = (float)img.cols;
    float height  = (float)img.rows;
    float widthPercent = width*percent;
    float heighPercent = height*percent;

    // from points
    src_p[0] = cv::Point2f(0.0f, 0.0f);     //top left corner
    src_p[1] = cv::Point2f(width, 0.0f);    //top right corner
    src_p[2] = cv::Point2f(width, height);   //bottom right corner
    src_p[3] = cv::Point2f(0.0f, height);    //bottom left corner

    // to points
    //Point2F(OX, -OY)
    float x_axis_start = -1* widthPercent;
    float x_axis_end = widthPercent+width;
    float y_axis_start = -1*heighPercent;
    float y_axis_end = heighPercent+height;

    dst_p[0] = cv::Point2f(x_axis_start, y_axis_start);
    dst_p[1] = cv::Point2f(x_axis_end, y_axis_start);
    dst_p[2] = cv::Point2f(x_axis_end, y_axis_end);
    dst_p[3] = cv::Point2f(x_axis_start, y_axis_end);

    qDebug()<<"x_axis_start: "<<x_axis_start<<"\n\
        x_axis_end: "<<x_axis_end<<"\n\
              y_axis_start: "<<y_axis_start<<"\n\
              y_axis_end: "<<y_axis_end<<"\n";

        // create perspective transform matrix 3x3
              cv::Mat trans_M3x3 = cv::getPerspectiveTransform(src_p, dst_p);

    // perspective transform operation using transform matrix
    cv::warpPerspective(img, img, trans_M3x3, img.size(), cv::INTER_LINEAR );
}
}
