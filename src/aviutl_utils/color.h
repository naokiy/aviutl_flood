#pragma once
namespace aviutl_utils {
	struct Color_RGBA {
		Color_RGBA(unsigned char b, unsigned char g, unsigned char r, unsigned char a) : b(b), g(g), r(r), a(a) {};
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};

	struct Color_RGB {
		Color_RGB(unsigned char b, unsigned char g, unsigned char r) : b(b), g(g), r(r) {};
		unsigned char b;
		unsigned char g;
		unsigned char r;
	};
}
