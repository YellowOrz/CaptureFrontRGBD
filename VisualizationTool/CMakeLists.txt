cmake_minimum_required(VERSION 2.8)
project(VisualizationTool)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(visualization visualization.cpp)
target_link_libraries(visualization ${OpenCV_LIBS})


