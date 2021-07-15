#include "matrix.h"
#include "distortion/distortion_common.h"

using namespace distortion::matrixDistortion;

MatrixDistortion::MatrixDistortion() {
    this->kernel1 = cv::Mat(3,3, CV_32FC1);
    this->kernel2 = cv::Mat(3,3, CV_32FC1);
    this->description.type = "matrixDistortion";
    this->description.category = "Matrix Distortion";
    this->description.name = "Matrix Distortion";
    this->description.explanation = "Change of individual pixels in the matrix 3x3";
    this->description.tooltip = "Change of individual pixels";

    this->description.arguments["kernelMin11"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin11" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin12"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin12" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin13"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin13" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin21"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin21" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin22"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin22" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin23"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin23" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin31"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin31" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin32"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin32" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMin33"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMin33" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax11"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax11" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax12"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax12" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax13"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax13" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax21"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax21" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax22"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax22" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax23"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax23" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax31"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax31" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax32"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax32" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
    this->description.arguments["kernelMax33"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "kernelMax33" },
                   { "value", 0 },
                   { "min", -100 },
                   { "max", 100 } };
}

Distortion* MatrixDistortion::cloneFromDescription(
  DistortionDescription description) const {
    auto* clone = new MatrixDistortion(*this);
    clone->kernel1.at<float>(0,0) =
      description.arguments["kernelMin11"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(0,1) =
      description.arguments["kernelMin12"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(0,2) =
      description.arguments["kernelMin13"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(1,0) =
      description.arguments["kernelMin21"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(1,1) =
      description.arguments["kernelMin22"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(1,2) =
      description.arguments["kernelMin23"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(2,0) =
      description.arguments["kernelMin31"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(2,1) =
      description.arguments["kernelMin32"].toObject()["value"].toDouble();
    clone->kernel1.at<float>(2,2) =
      description.arguments["kernelMin33"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(0,0) =
      description.arguments["kernelMax11"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(0,1) =
      description.arguments["kernelMax12"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(0,2) =
      description.arguments["kernelMax13"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(1,0) =
      description.arguments["kernelMax21"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(1,1) =
      description.arguments["kernelMax22"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(1,2) =
      description.arguments["kernelMax23"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(2,0) =
      description.arguments["kernelMax31"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(2,1) =
      description.arguments["kernelMax32"].toObject()["value"].toDouble();
    clone->kernel2.at<float>(2,2) =
      description.arguments["kernelMax33"].toObject()["value"].toDouble();
    return clone;
}

QString MatrixDistortion::stringOfInternalValues() const {
    return QString("kernelMin11: %0; kernelMin12: %1; kernelMin13: %2; "
                "kernelMin21: %3; kernelMin22: %4; kernelMin23: %5;"
                "kernelMin31: %6; kernelMin32: %7; kernelMin33: %8;"
                "kernelMax11: %9; kernelMax12: %10; kernelMax13: %11;"
                "kernelMax21: %12; kernelMax22: %13; kernelMax23: %14;"
                "kernelMax31: %15; kernelMax32: %16; kernelMax33: %17")
        .arg(this->kernel1.at<float>(0,0))
        .arg(this->kernel1.at<float>(0,1))
        .arg(this->kernel1.at<float>(0,2))
        .arg(this->kernel1.at<float>(1,0))
        .arg(this->kernel1.at<float>(1,1))
        .arg(this->kernel1.at<float>(1,2))
        .arg(this->kernel1.at<float>(2,0))
        .arg(this->kernel1.at<float>(2,1))
        .arg(this->kernel1.at<float>(2,2))
        .arg(this->kernel2.at<float>(0,0))
        .arg(this->kernel2.at<float>(0,1))
        .arg(this->kernel2.at<float>(0,2))
        .arg(this->kernel2.at<float>(1,0))
        .arg(this->kernel2.at<float>(1,1))
        .arg(this->kernel2.at<float>(1,2))
        .arg(this->kernel2.at<float>(2,0))
        .arg(this->kernel2.at<float>(2,1))
        .arg(this->kernel2.at<float>(2,2));
}

void MatrixDistortion::distort(cv::Mat& img) const {
    //kernel 3x3 (3,3, CV_32FC1)
    qDebug()<<"matrixDistortion start";

    cv::Mat kernel = cv::Mat::zeros(3,3, CV_32FC1);

    for(int i = 0; i < kernel.cols; i++)
        for(int j = 0; j < kernel.rows; j++){
            kernel.at<float>(i,j) = distortion::randomReal(kernel1.at<float>(i,j), kernel2.at<float>(i,j));
        }
    cv::filter2D(img, img, -1, kernel);
}
