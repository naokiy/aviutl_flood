# CMakeList.txt : CMakFlood の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 2.8)

project(flood)

find_package(Lua51 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/aviutl_utils
	${LUA_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIRS}
	)

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.def ${PROJECT_SOURCE_DIR}/aviutl_utils/*.cpp)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_library(flood SHARED ${SRC_FILES})

target_link_libraries(flood ${LUA_LIBRARIES} ${OpenCV_LIBS})