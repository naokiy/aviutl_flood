#pragma once

namespace aviutl_utils {
	struct Point {
		Point() : x(0), y(0) {};
		Point(int x, int y) : x(x), y(y) {};
		int x;
		int y;
	};
}