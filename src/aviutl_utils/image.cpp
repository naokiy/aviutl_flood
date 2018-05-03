#include "image.h"

namespace aviutl_utils {

	Image::Image(Color_RGBA * source, int source_width, int source_height)
	{
		image = source;
		width = source_width;
		height = source_height;
	}

	Image::~Image()
	{
	}

	int Image::get_width()
	{
		return width;
	}

	int Image::get_height()
	{
		return height;
	}

	bool Image::is_empty()
	{
		return (width == 0 || height == 0);
	}

	Color_RGBA Image::get_rgba_at(Point p)
	{
		return image[p.y * width + p.x];
	}

	Color_RGB Image::get_rgb_at(Point p)
	{
		Color_RGBA rgba = image[p.y * width + p.x];
		return { rgba.b, rgba.g, rgba.r };
	}

	void Image::set_rgba_at(Point p, Color_RGBA color)
	{
		image[p.y * width + p.x] = color;
	}

	void Image::set_rgb_at(Point p, Color_RGB color)
	{
		unsigned long pos = p.y * width + p.x;
		image[pos].b = color.b;
		image[pos].g = color.g;
		image[pos].r = color.r;
	}

	void Image::set_alpha_at(Point p, unsigned char alpha)
	{
		image[p.y * width + p.x].a = alpha;
	}

	Point Image::fix_point(Point p)
	{
		Point new_p = Point();
		new_p.x = (p.x < 0) ? 0 : (p.x > width - 1) ? width - 1: p.x;
		new_p.y = (p.y < 0) ? 0 : (p.y > width - 1) ? height - 1: p.y;

		return new_p;
	}
}