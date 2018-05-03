#pragma once

#include "opencv2/core.hpp"
#include "color.h"
#include "image.h"
#include "point.h"


namespace aviutl_utils {

	cv::Scalar cv_scalar(Color_RGB color);
	cv::Vec3b cv_vector(Color_RGB color);

	cv::Scalar cv_scalar(int x);

	cv::Mat cv_mat(Image image);

	cv::Point cv_point(Point point);

}