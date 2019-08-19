# 检查CMake版本
cmake_minimum_required(VERSION 3.3)

# project名称
project (pattern)

# 将include目录添加到include的搜索路径中,PROJECT_SOURCE_DIR为当前工程根目录
include_directories ("${PROJECT_SOURCE_DIR}/include")

# 生成debug/release版本
SET(CMAKE_BUILD_TYPE "release")
#SET(CMAKE_BUILD_TYPE "debug")
if (CMAKE_BUILD_TYPE STREQUAL debug)
    add_definitions(-D_DEBUG)
endif ()
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall ")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -W ")

aux_source_directory(. SRC_LIST_C  ) 

# 设置可执行文件
add_executable(pattern ${SRC_LIST_C} )
