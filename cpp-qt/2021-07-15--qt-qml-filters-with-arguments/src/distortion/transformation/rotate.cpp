#include "rotate.h"
#include "transformation_json_object.h"
#include "distortion/distortion_common.h"

namespace distortion::transformation{
Rotate::Rotate(){
    this->description.type = "Rotate";
    this->description.category = "Modification";
    this->description.name = "Rotate";
    this->description.explanation = "Rotate image a randomly selected degree within the specified range";
    this->description.tooltip = "Rotate image";
    this->description.arguments["degreeMin"] =
            createQJsonObject("double spin box","Degree Min",-360,360,0);
    this->description.arguments["degreeMax"] =
            createQJsonObject("double spin box","Degree Max",-360,360,0);
}
//-----------------------------------------------------------------------------------
Distortion* Rotate::cloneFromDescription(DistortionDescription description) const{
    auto* clone = new Rotate(*this);
    clone->degreeMin =
            description.arguments["degreeMin"].toObject()["value"].toDouble();
    clone->degreeMax =
            description.arguments["degreeMax"].toObject()["value"].toDouble();
    return clone;
}
//-----------------------------------------------------------------------------------
QString Rotate::stringOfInternalValues() const {
    return QString("degreeMin: %0; degreeMax: %1")
            .arg(this->degreeMin)
            .arg(this->degreeMax);
}
//-----------------------------------------------------------------------------------
void Rotate::distort(cv::Mat &image) const{
    qDebug()<<"rotate function start";
    int degree = randomInt(degreeMin, degreeMax);
    cv::Mat frame, frameRotated;
    int diagonal = (int)sqrt(image.cols * image.cols + image.rows * image.rows);
    int newWidth = diagonal;
    int newHeight = diagonal;
    int offsetX = (newWidth - image.cols) / 2;
    int offsetY = (newHeight - image.rows) / 2;
    cv::Mat targetMat(newWidth, newHeight, image.type());
    cv::Point2f image_center(targetMat.cols/2.0F, targetMat.rows/2.0F);

    image.copyTo(frame);
    frame.copyTo(targetMat.rowRange(offsetY, offsetY + frame.rows).colRange(offsetX, offsetX + frame.cols));
    cv::Mat rot_mat = getRotationMatrix2D(image_center, degree, 1.0);
    warpAffine(targetMat, frameRotated, rot_mat, targetMat.size());
    cv::Rect bound_Rect(frame.cols, frame.rows, 0, 0);

    int x1 = offsetX;
    int x2 = offsetX+frame.cols;
    int x3 = offsetX;
    int x4 = offsetX+frame.cols;

    int y1 = offsetY;
    int y2 = offsetY;
    int y3 = offsetY+frame.rows;
    int y4 = offsetY+frame.rows;

    cv::Mat Coordinates = (cv::Mat_<double>(3,4) << x1, x2, x3, x4,
                           y1, y2, y3, y4,
                           1,  1,  1,  1 );
    cv::Mat RotCoordinate = rot_mat * Coordinates;

    for(int i = 0; i < 4; i++){
        if(RotCoordinate.at<double>(0,i) < bound_Rect.x)
            bound_Rect.x = (int)RotCoordinate.at<double>(0,i);
        if(RotCoordinate.at<double>(1,i) < bound_Rect.y)
            bound_Rect.y = RotCoordinate.at<double>(1,i);
    }
    for(int i = 0; i < 4; i++){
        if(RotCoordinate.at<double>(0,i) > bound_Rect.width)
            bound_Rect.width = (int)RotCoordinate.at<double>(0,i);
        if(RotCoordinate.at<double>(1,i) > bound_Rect.height)
            bound_Rect.height = RotCoordinate.at<double>(1,i);
    }

    bound_Rect.width = bound_Rect.width - bound_Rect.x;
    bound_Rect.height = bound_Rect.height - bound_Rect.y;

    cv::Mat ROI = frameRotated(bound_Rect);
    ROI.copyTo(image);
}
}
