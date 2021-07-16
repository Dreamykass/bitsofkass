#include "sobel.h"
#include "distortion/distortion_common.h"

using namespace distortion::edge_detection;

Sobel::Sobel(){
    this->description.type = "sobel";
    this->description.category = "Edge detection";
    this->description.name = "Sobel";
    this->description.explanation = "Edge detection.\n"
                                    "The Sobel Operator is a discrete differentiation operator. "
                                    "It computes an approximation of the gradient of an image intensity function.\n"
                                    "Before using this method, it is recommended that you use a gaussian filter.\n"
                                    "Kernel variables is responible for number of edges generated. Range 0-5.\n"
                                    "Delta variables is responible for lightening, consequently show more details. Range 0-100.";
    this->description.tooltip = "Before using this method, it is recommended that you use a gaussian filter.";

    this->description.arguments["kMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Kernel Min" },
                   { "value", 0 },
                   { "min", 0 },
                   { "max", 5 } };
    this->description.arguments["kMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Kernel Max" },
                   { "value", 1 },
                   { "min", 1 },
                   { "max", 5 } };
    this->description.arguments["dMin"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Delta Min" },
                   { "value", 1 },
                   { "min", 0 },
                   { "max", 100 } };
    this->description.arguments["dMax"] =
      QJsonObject{ { "type", "double spin box" },
                   { "name", "Delta Max" },
                   { "value", 20 },
                   { "min", 1 },
                   { "max", 100 } };
}

Distortion* Sobel::cloneFromDescription(
        DistortionDescription description) const {
    auto* clone = new Sobel(*this);
    clone->kMin =
      description.arguments["kMin"].toObject()["value"].toInt();
    clone->kMax =
      description.arguments["kMax"].toObject()["value"].toInt();
    clone->dMin =
      description.arguments["dMin"].toObject()["value"].toInt();
    clone->dMax =
      description.arguments["dMax"].toObject()["value"].toInt();
    return clone;
}

QString Sobel::stringOfInternalValues() const {
    return QString("kMin: %0; kMax: %1; dMin: %2; dMax: %3")
      .arg(this->kMin)
      .arg(this->kMax)
      .arg(this->dMin)
      .arg(this->dMax);
}

void Sobel::distort(cv::Mat& img) const {
    qDebug()<<"sobel start";
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    int ksize;
    do{
        ksize = distortion::randomInt(kMin, kMax);
    }while(ksize == 2 || ksize == 4);
    int scale = -1;
    int delta = distortion::randomInt(dMin, dMax);

    cv::cvtColor(img, img, cv::COLOR_RGBA2GRAY);
    cv::cvtColor(img, img, cv::COLOR_GRAY2RGBA);
    cv::Sobel(img, grad_x, CV_16S, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);
    cv::Sobel(img, grad_y, CV_16S, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, img);
}
