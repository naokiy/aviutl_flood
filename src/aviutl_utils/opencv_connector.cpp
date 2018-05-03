#include "opencv_connector.h"

namespace aviutl_utils{

	cv::Scalar cv_scalar(Color_RGB color)
	{
		return cv::Scalar(color.b, color.g, color.r);
	}

	cv::Vec3b cv_vector(Color_RGB color)
	{
		return cv::Vec3b(color.b, color.g, color.r);
	}

	cv::Scalar cv_scalar(int x)
	{
		return cv::Scalar(x,x,x);
	}

	cv::Mat cv_mat(Image image)
	{
		
		int width = image.get_width();
		int height = image.get_height();

		int x, y;

		cv::Mat result = cv::Mat::zeros(height, width, CV_8UC3);

#pragma omp parallel for private(x) schedule(guided)
		for (y = 0; y < height; y++) {
			cv::Vec3b* ptr = result.ptr<cv::Vec3b>(y);
			for (x = 0; x < width; x++) {
				unsigned long pos = y * width + x;
				ptr[x] = cv_vector(image.get_rgb_at({ x, y }));
			}
		}

		return result;
	}

	cv::Point cv_point(Point point)
	{
		return cv::Point(point.x, point.y);
	}

}