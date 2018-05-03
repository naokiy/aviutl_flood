#pragma once

#include "lua.hpp"

#include "color.h"
#include "point.h"
#include "image.h"

namespace aviutl_utils {

	class LuaLoader
	{
		lua_State *L;
		int index;
	public:
		LuaLoader(lua_State *L);
		~LuaLoader();
		int get_integer();
		Color_RGB get_color();
		Image get_image();
		Point get_point();
	};

}