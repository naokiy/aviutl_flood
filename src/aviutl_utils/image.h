#pragma once

#include "color.h"
#include "point.h"

namespace aviutl_utils {
	class Image
	{
		Color_RGBA* image;
		int width;
		int height;
	public:
		Image(Color_RGBA* source, int source_width, int source_height);
		~Image();
		int get_width();
		int get_height();
		bool is_empty();
		Color_RGBA get_rgba_at(Point p);
		Color_RGB get_rgb_at(Point p);

		void set_rgba_at(Point p, Color_RGBA color);
		void set_rgb_at(Point p, Color_RGB color);
		void set_alpha_at(Point p, unsigned char alpha);
		Point fix_point(Point p);
	};
}