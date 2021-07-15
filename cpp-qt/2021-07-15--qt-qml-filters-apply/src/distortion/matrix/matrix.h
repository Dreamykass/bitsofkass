#ifndef MATRIX_H
#define MATRIX_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace distortion::matrixDistortion {
class MatrixDistortion : public Distortion {
  public:
    MatrixDistortion();
    Distortion* cloneFromDescription(DistortionDescription) const override;
    QString stringOfInternalValues() const override;
    void distort(cv::Mat&) const override;
  private:
    cv::Mat kernel1;
    cv::Mat kernel2;
};
}

#endif // MATRIX_H
