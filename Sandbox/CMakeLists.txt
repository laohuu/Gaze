cmake_minimum_required(VERSION 3.23)
project(Sandbox VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

file(GLOB_RECURSE SOURCES Source/*.h Source/*.cpp)
add_executable(Sandbox ${SOURCES})

target_include_directories(Sandbox PRIVATE
        ../Gaze/Source
        )

target_link_libraries(Sandbox PRIVATE Gaze glfw)