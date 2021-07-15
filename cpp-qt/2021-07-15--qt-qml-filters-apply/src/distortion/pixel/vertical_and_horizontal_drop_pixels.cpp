#include "vertical_and_horizontal_drop_pixels.h"
#include "distortion/distortion_common.h"

namespace distortion::pixel {
    VerticalAndHorizontalDropPixels::VerticalAndHorizontalDropPixels() {
        this->description.type = "verticalandhorizontaldropPixels";
        this->description.category = "Pixel";
        this->description.name = "VerticalAndHorizontalDropPixels";
        this->description.explanation = "The function removes the selected pixels in rows, from the given number of steps.\n"
                                        "Variable range from 0 to 100.";
        this->description.tooltip = "Remove pixels.";
        this->description.arguments["verticalRowStepDeleteMin"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Vertical Step Min" },
                       { "value", 2 },
                       { "min", 1 },
                       { "max", 100 } };
        this->description.arguments["verticalRowStepDeleteMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Vertical Step Max" },
                       { "value", 2 },
                       { "min", 1 },
                       { "max", 100 } };
        this->description.arguments["horizontalRowStepDeleteMin"] =
          QJsonObject{ { "type", "Horizontal Step Min" },
                       { "name", "Step Min" },
                       { "value", 2 },
                       { "min", 1 },
                       { "max", 100 } };
        this->description.arguments["horizontalRowStepDeleteMax"] =
          QJsonObject{ { "type", "double spin box" },
                       { "name", "Horizontal Step Max" },
                       { "value", 2 },
                       { "min", 1 },
                       { "max", 100 } };
    }
    Distortion* VerticalAndHorizontalDropPixels::cloneFromDescription(
      DistortionDescription description) const {
        auto* clone = new VerticalAndHorizontalDropPixels(*this);
        clone->verticalRowStepDeleteMin =
          description.arguments["verticalRowStepDeleteMin"].toObject()["value"].toDouble();
        clone->verticalRowStepDeleteMax =
          description.arguments["verticalRowStepDeleteMax"].toObject()["value"].toDouble();
        clone->horizontalRowStepDeleteMin =
          description.arguments["horizontalRowStepDeleteMin"].toObject()["value"].toDouble();
        clone->horizontalRowStepDeleteMax =
          description.arguments["horizontalRowStepDeleteMax"].toObject()["value"].toDouble();
        return clone;
    }
    QString VerticalAndHorizontalDropPixels::stringOfInternalValues() const {
        return QString("verticalRowStepDeleteMin: %0; verticalRowStepDeleteMax: %1, horizontalRowStepDeleteMin: %2; horizontalRowStepDeleteMax: %3")
          .arg(this->verticalRowStepDeleteMin)
          .arg(this->verticalRowStepDeleteMax)
          .arg(this->horizontalRowStepDeleteMin)
          .arg(this->horizontalRowStepDeleteMax);
    }
    void VerticalAndHorizontalDropPixels::distort(cv::Mat& image) const {
        if(verticalRowStepDeleteMin==0 && verticalRowStepDeleteMax==0)
            if(horizontalRowStepDeleteMin==0 && horizontalRowStepDeleteMax==0)
                return;
            else
                horizontalDrop(image);
        else
            if(horizontalRowStepDeleteMin==0 && horizontalRowStepDeleteMax==0)
                verticalDrop(image);
            else
                bothDrop(image);
    }

    void VerticalAndHorizontalDropPixels::verticalDrop(cv::Mat& image) const{
        qDebug()<<"verticalDropPixels start";
        cv::Mat map_x(image.size(), CV_32FC1);
        cv::Mat map_y(image.size(), CV_32FC1);

        int rowStepDelete = randomInt(verticalRowStepDeleteMin, verticalRowStepDeleteMax);

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

    void VerticalAndHorizontalDropPixels::horizontalDrop(cv::Mat &image) const{
        qDebug()<<"horizontalDropPixels start";
        cv::Mat map_x(image.size(), CV_32FC1);
        cv::Mat map_y(image.size(), CV_32FC1);

        int rowStepDelete = randomInt(horizontalRowStepDeleteMin, horizontalRowStepDeleteMax);

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

    void VerticalAndHorizontalDropPixels::bothDrop(cv::Mat &image) const{
        qDebug()<<"verticalDropPixels start";
        cv::Mat map_x(image.size(), CV_32FC1);
        cv::Mat map_y(image.size(), CV_32FC1);


        int verticalRowStepDelete = randomInt(verticalRowStepDeleteMin, verticalRowStepDeleteMax);
        int horizontalRowStepDelete = randomInt(horizontalRowStepDeleteMin, horizontalRowStepDeleteMax);

        //update map
        for( int i = 0; i < image.rows; i++ )
        {
            if(i%horizontalRowStepDelete==0)
                continue;
            for( int j = 0; j < image.cols; j++ )
            {
                if(j%verticalRowStepDelete==0)
                    continue;
                map_x.at<float>(i, j) = (float)(j);
                map_y.at<float>(i, j) = (float)(i);
            }
        }
        //map
        cv::remap(image, image, map_x, map_y, cv::INTER_LINEAR);
    }
}
