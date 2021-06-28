#include <QString>
#include <opencv2/opencv.hpp>

struct Model {
  // RGBA format
  cv::Mat originalMat;

  // RGBA format
  cv::Mat transformedMat;

  bool grayscale = false;
  bool inverted = false;
  bool noRed = false;
  bool noGreen = false;
  bool noBlue = false;
  double sizeModifier = 1.0;
};
