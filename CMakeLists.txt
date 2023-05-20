cmake_minimum_required(VERSION 3.23)
project(GazeEngine VERSION 0.1.0)

include_directories(Gaze/Packages/spdlog/include)
#include_directories(Gaze/Packages/spdlog)
#include_directories(Gaze/Packages)

add_subdirectory(Gaze)
add_subdirectory(Sandbox)
