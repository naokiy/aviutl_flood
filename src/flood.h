#pragma once

#include "lua.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

#include "aviutl_utils/lua_loader.h"
#include "aviutl_utils/opencv_connector.h"

int luaopen_flood(lua_State* L);
