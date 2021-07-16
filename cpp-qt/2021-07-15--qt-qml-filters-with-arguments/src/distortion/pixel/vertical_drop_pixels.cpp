#include "vertical_drop_pixels.h"
#include "distortion/distortion_common.h"

namespace distortion::pixel {
    VerticalDropPixels::VerticalDropPixels() {
        this->description.type = "verticalDropPixels";
        this->description.category = "Pixel";
        this->description.name = "VerticalDropPixels";
        this->description.explanation = "The function removes the selected pixels in rows, from the given number of steps.\n"
                                        "Variable range from 0 to 100.";
        this->description.tooltip = "Remove pixels.";
        this->description.arguments["stepDeleteMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Step Min" },
                       { "value", 2 },
                       { "min", 1 },
                       { "max", 100 } };
        this->description.arguments["stepDeleteMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Step Max" },
                       { "value", 2 },
                       { "min", 1 },
                       { "max", 100 } };
    }
    Distortion* VerticalDropPixels::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new VerticalDropPixels(*this);
        clone->stepDeleteMin =
          description.arguments["stepDeleteMin"].toObject()["value"].toDouble();
        clone->stepDeleteMax =
          description.arguments["stepDeleteMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString VerticalDropPixels::stringOfInternalValues() const {
        return QString("stepDeleteMin: %0; stepDeleteMax: %1")
          .arg(this->stepDeleteMin)
          .arg(this->stepDeleteMax);
    }
    void VerticalDropPixels::distort(cv::Mat& image) const {
        qDebug()<<"verticalDropPixels start";
        cv::Mat map_x(image.size(), CV_32FC1);
        cv::Mat map_y(image.size(), CV_32FC1);

        int rowStepDelete = randomInt(stepDeleteMin, stepDeleteMax);

        //update map
        for( int i = 0; i < image.rows; i++ )
        {
            for( int j = 0; j < image.cols; j++ )
            {
                if(j%rowStepDelete==0)
                    continue;
                map_x.at<float>(i, j) = (float)(j);
                map_y.at<float>(i, j) = (float)(i);
            }
        }
        //map
        cv::remap(image, image, map_x, map_y, cv::INTER_LINEAR);
    }
}
