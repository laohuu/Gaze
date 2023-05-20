cmake_minimum_required(VERSION 3.23)
project(Gaze_Engine VERSION 0.1.0)

include_directories(Gaze/Packages/spdlog/include)

add_subdirectory(Gaze)
add_subdirectory(Sandbox)
