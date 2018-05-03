#include "lua_loader.h"

namespace aviutl_utils {
	LuaLoader::LuaLoader(lua_State * L)
	{
		this->L = L;
		this->index = 0;
	}

	LuaLoader::~LuaLoader()
	{
	}

	int LuaLoader::get_integer()
	{
		return lua_tointeger(L, ++index);
	}

	Color_RGB LuaLoader::get_color()
	{
		int from = lua_tointeger(L, ++index);
		unsigned char r = from >> 16 & 0xFF;
		unsigned char g = from >> 8 & 0xFF;
		unsigned char b = from & 0xFF;
		return { b, g, r };
	}

	Image LuaLoader::get_image()
	{
		Color_RGBA* image = (Color_RGBA*)lua_touserdata(L, ++index);
		int width = lua_tointeger(L, ++index);
		int height = lua_tointeger(L, ++index);

		return Image(image, width, height);
	}

	Point LuaLoader::get_point()
	{
		int x = lua_tointeger(L, ++index);
		int y = lua_tointeger(L, ++index);
		return { x, y };
	}
}