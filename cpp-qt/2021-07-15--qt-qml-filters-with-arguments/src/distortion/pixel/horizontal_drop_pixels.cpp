#include "horizontal_drop_pixels.h"
#include "distortion/distortion_common.h"

namespace distortion::pixel {
    HorizontalDropPixels::HorizontalDropPixels() {
        this->description.type = "horizontaldroppixels";
        this->description.category = "Pixel";
        this->description.name = "HorizontalDropPixels";
        this->description.explanation = "The function removes the selected pixels, from the given number of steps.\n"
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
    Distortion* HorizontalDropPixels::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new HorizontalDropPixels(*this);
        clone->stepDeleteMin =
          description.arguments["stepDeleteMin"].toObject()["value"].toDouble();
        clone->stepDeleteMax =
          description.arguments["stepDeleteMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString HorizontalDropPixels::stringOfInternalValues() const {
        return QString("stepDeleteMin: %0; stepDeleteMax: %1")
          .arg(this->stepDeleteMin)
          .arg(this->stepDeleteMax);
    }
    void HorizontalDropPixels::distort(cv::Mat& image) const {
        qDebug()<<"horizontalDropPixels start";
        cv::Mat map_x(image.size(), CV_32FC1);
        cv::Mat map_y(image.size(), CV_32FC1);

        int rowStepDelete = randomInt(stepDeleteMin, stepDeleteMax);

        //update map
        //rows loop
        for( int i = 0; i < image.rows; i++ )
        {
            if(i%rowStepDelete==0)
                continue;
            //cols rows
            for( int j = 0; j < image.cols; j++ )
            {
                //horizontal j-column(width) number
                map_x.at<float>(i, j) = (float)(j);
                //vertical i-rows(height) number
                map_y.at<float>(i, j) = (float)(i);
            }
        }
        //map
        cv::remap(image, image, map_x, map_y, cv::INTER_LINEAR);
    }
}
