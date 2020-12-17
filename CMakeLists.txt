cmake_minimum_required(VERSION 3.17)
project(POC)

set(CMAKE_CXX_STANDARD 14)
# 添加头文件路径链接
include_directories(include)

add_executable(POC main.cpp)

file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
#    target_link_libraries(${exe} libopengl32.a libfreeglut.a glu32.lib glew32.lib glfw3)
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()