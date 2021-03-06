#include "flood.h"

using namespace cv;

cv::Mat make_mask(aviutl_utils::Image source, int lo_diff, int up_diff, int fixed_range, int target_count, aviutl_utils::Point points[]) {

	cv::Mat image = aviutl_utils::cv_mat(source);

	cv::Mat image_mask = cv::Mat::zeros(source.get_height() + 2, source.get_width() + 2, CV_8UC1);

	int flags = 4 | ((fixed_range != 0) ? FLOODFILL_FIXED_RANGE : 0);
	flags |= FLOODFILL_MASK_ONLY;
	flags |= (255 << 8);

	cv::Scalar scalar_lo_diff = aviutl_utils::cv_scalar(lo_diff);
	cv::Scalar scalar_up_diff = aviutl_utils::cv_scalar(up_diff);

	for (int i = 0; i < target_count; ++i) {
		aviutl_utils::Point point = source.fix_point(points[i]);
		cv::Point target_point = aviutl_utils::cv_point(point);
		cv::floodFill(image, image_mask, target_point, cv::Scalar(0, 0, 0), NULL, scalar_lo_diff, scalar_up_diff, flags);
	}

	return image_mask;
}

static int flood_mtgo_table(lua_State* L) {
	aviutl_utils::LuaLoader loader = aviutl_utils::LuaLoader(L);

	aviutl_utils::Image table_source = loader.get_image();
	if (table_source.is_empty()) {
		return 0;
	}
	cv::Mat table_image = aviutl_utils::cv_mat(table_source);

	aviutl_utils::Image playmat_source = loader.get_image();
	if (playmat_source.is_empty()) {
		return 0;
	}

	aviutl_utils::Point offset = loader.get_point();

	int target_num = loader.get_integer();

	aviutl_utils::Point *points = new aviutl_utils::Point[target_num];

	for (int i = 0; i < target_num; ++i) {
		points[i] = loader.get_point();
	}

	int fixed_range = 0;

	int lo_diff = 13;
	int up_diff = 13;


	cv::Mat image_mask = make_mask(table_source, lo_diff, up_diff, fixed_range, target_num, points);

	int x, y;

	int min_x = (offset.x > 0) ? offset.x : 0;
	int max_x = (table_source.get_width() < (offset.x + playmat_source.get_width())) ? table_source.get_width() : offset.x + playmat_source.get_width();
	int min_y = (offset.y > 0) ? offset.y : 0;
	int max_y = (table_source.get_height() < (offset.y + playmat_source.get_height())) ? table_source.get_height() : offset.y + playmat_source.get_height();


#pragma omp parallel for private(y) schedule(guided)
	for (y = min_y; y < max_y; y++) {
		unsigned char* ptr = image_mask.ptr<unsigned char>(y + 1);
		for (x = min_x; x < max_x; x++) {
			unsigned char alpha = ptr[x + 1];
			if (alpha == 0) {
				continue;
			}

			aviutl_utils::Color_RGBA table_color = table_source.get_rgba_at({ x, y });
			aviutl_utils::Color_RGBA playmat_color = playmat_source.get_rgba_at({ x - offset.x, y - offset.y });

			aviutl_utils::Color_RGBA new_color = playmat_color;

			if (table_color.g < 90) {
				new_color = aviutl_utils::Color_RGBA(new_color.b / 2, new_color.g / 2, new_color.r / 2, new_color.a);
			}

			table_source.set_rgba_at({ x, y }, new_color);

		}
	}

	return 0;
}

static int flood_clear(lua_State* L) {
	aviutl_utils::LuaLoader loader = aviutl_utils::LuaLoader(L);

	aviutl_utils::Image source = loader.get_image();
	if (source.is_empty()) {
		return 0;
	}

	aviutl_utils::Point *points = new aviutl_utils::Point[1];
	points[0] = loader.get_point();

	int lo_diff = loader.get_integer();
	int up_diff = loader.get_integer();

	int fixed_range = loader.get_integer();

	cv::Mat image_mask = make_mask(source, lo_diff, up_diff, fixed_range, 1, points);

	int x, y;

#pragma omp parallel for private(y) schedule(guided)
	for (y = 0; y < source.get_height(); y++) {
		unsigned char* ptr = image_mask.ptr<unsigned char>(y + 1);
		for (x = 0; x < source.get_width(); x++) {
			unsigned char alpha = ptr[x + 1];
			if (alpha != 0) {
				source.set_alpha_at({ x, y }, 0);
			}
		}
	}

	return 0;
}

static int flood_fill(lua_State* L) {
	aviutl_utils::LuaLoader loader = aviutl_utils::LuaLoader(L);

	aviutl_utils::Image source = loader.get_image();
	if (source.is_empty()) {
		return 0;
	}
	cv::Mat image = aviutl_utils::cv_mat(source);

	aviutl_utils::Point target = loader.get_point();
	target = source.fix_point(target);
	cv::Point target_point = aviutl_utils::cv_point(target);

	cv::Scalar lo_diff = aviutl_utils::cv_scalar(loader.get_integer());
	cv::Scalar up_diff = aviutl_utils::cv_scalar(loader.get_integer());
	cv::Scalar color = aviutl_utils::cv_scalar(loader.get_color());

	int fixed_range = loader.get_integer();

	int flags = 4 | ((fixed_range != 0) ? FLOODFILL_FIXED_RANGE : 0);

	cv::floodFill(image, target_point, color, NULL, lo_diff, up_diff, flags);

	int x, y;

#pragma omp parallel for private(y) schedule(guided)
	for (y = 0; y < source.get_height(); y++) {
		cv::Vec3b* ptr = image.ptr<cv::Vec3b>(y);
		for (x = 0; x < source.get_width(); x++) {
			cv::Vec3b bgr = ptr[x];
			source.set_rgb_at({ x,y }, { bgr[0], bgr[1], bgr[2] });
		}
	}

	return 0;
}

const luaL_Reg functiontable[] = {
	{ "fill", flood_fill },
{ "clear", flood_clear },
{ "mtgo_table", flood_mtgo_table },
{ NULL, NULL }
};

int luaopen_flood(lua_State* L) {
	luaL_register(L, "flood", functiontable);
	return 1;
}