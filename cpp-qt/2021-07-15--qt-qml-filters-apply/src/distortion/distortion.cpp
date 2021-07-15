#include <vector>
#include "distortion.h"
#include "distortion/noise/classicnoise.h"
#include "distortion/noise/opensimplex2.h"
#include "distortion/noise/opensimplex2s.h"
#include "distortion/noise/perlin.h"
#include "distortion/noise/cellular.h"
#include "distortion/noise/value.h"
#include "distortion/noise/value_cubic.h"
#include "distortion/optical/barrel.h"
#include "distortion/optical/pincushion.h"
#include "distortion/simple_color/brightness.h"
#include "distortion/simple_color/contrast.h"
#include "distortion/simple_color/grayscale.h"
#include "distortion/simple_color/inverted.h"
#include "distortion/simple_color/noblue.h"
#include "distortion/simple_color/nored.h"
#include "distortion/simple_color/nogreen.h"
#include "distortion/flip_image/flip_vertically.h"
#include "distortion/flip_image/flip_horizontally.h"
#include "distortion/compression/jpeg.h"
#include "distortion/optical/barrel.h"
#include "distortion/optical/pincushion.h"
#include "distortion/transformation/cropping.h"
#include "distortion/transformation/proximity.h"
#include "distortion/transformation/rotate.h"
#include "distortion/transformation/scale_modifier.h"
#include "distortion/transformation/tilt.h"
#include "distortion/non_simple_color/change_image_color.h"
#include "distortion/non_simple_color/change_range_color.h"
#include "distortion/non_simple_color/filter2d.h"
#include "distortion/blur/bilateral_blur.h"
#include "distortion/blur/classic_blur.h"
#include "distortion/blur/gaussian_blur.h"
#include "distortion/blur/median_blur.h"
#include "distortion/pixel/pixelate.h"
#include "distortion/pixel/pixelatev2.h"
#include "distortion/pixel/horizontal_drop_pixels.h"
#include "distortion/pixel/vertical_drop_pixels.h"
#include "distortion/pixel/vertical_and_horizontal_drop_pixels.h"
#include "distortion/edge_detection/sobel.h"
#include "distortion/edge_detection/laplace.h"
#include "distortion/edge_detection/canny.h"
#include "distortion/matrix/matrix.h"

// ok here, in a .cpp file - no way for a name clash to occur
using namespace distortion;

QMap<QString, QSharedPointer<const Distortion>> getAllDefaultDistortions() {
    auto map = QMap<QString, QSharedPointer<const Distortion>>();

    for (auto* dist : std::vector<Distortion*>{
         // distortions go here
         new simple_color::Grayscale(),
         new simple_color::Brightness(),
         new simple_color::NoRed(),
         new simple_color::NoGreen(),
         new simple_color::NoBlue(),
         new simple_color::Contrast(),
         new simple_color::Inverted(),
         new noise::OpenSimplex2(),
         new noise::OpenSimplex2S(),
         new noise::Perlin(),
         new noise::Cellular(),
         new noise::Value(),
         new noise::ValueCubic(),
         new noise::ClassicNoise(),
         new flip_image::FlipHorizontally(),
         new flip_image::FlipVertically(),
         new compression::Jpeg(),
         new optical::Barrel(),
         new optical::Pincushion(),
         new non_simple_color::ChangeRangeColor(),
         new non_simple_color::ChangeImageColor(),
         new non_simple_color::Filter2D(),
         new pixel::Pixelate(),
         new pixel::Pixelatev2(),
         new pixel::HorizontalDropPixels(),
         new pixel::VerticalDropPixels(),
         new pixel::VerticalAndHorizontalDropPixels(),
         new blur::BilateralBlur(),
         new blur::GaussianBlur(),
         new blur::MedianBlur(),
         new blur::ClassicBlur(),
         new transformation::Cropping(),
         new transformation::Tilt(),
         new transformation::Rotate(),
         new transformation::Proximity(),
         new transformation::ScaleModifier(),
         new edge_detection::Sobel(),
         new edge_detection::Laplace(),
         new edge_detection::Canny(),
         new matrixDistortion::MatrixDistortion(),
           // distortions go here ^
         }) {
        auto scopedPtr = QSharedPointer<const Distortion>(dist);
        map.insert(scopedPtr->description.type, scopedPtr);
    }

    return map;
}

// here is only the implementation for distortion.h
// specific distortions should go to their respective files
