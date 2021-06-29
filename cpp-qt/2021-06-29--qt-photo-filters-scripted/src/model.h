#pragma once

#include <QString>
#include <opencv2/opencv.hpp>
#include <sol/sol.hpp>

struct Model {
  // RGBA format
  cv::Mat originalMat;

  // RGBA format
  cv::Mat transformedMat;

  // lua state
  sol::state lua;
};
