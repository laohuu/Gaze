cmake_minimum_required(VERSION 3.23)
project(Gaze VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(Packages)
add_compile_definitions(GZ_DEBUG)

file(GLOB_RECURSE SOURCES Source/*.h Source/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

if (WIN32)
elseif (UNIX AND NOT APPLE)
elseif (APPLE)
    set(GLFW_LINK Lib/GLFW/lib-arm64/libglfw.3.dylib)
    link_libraries(${GLFW_LINK})

    target_link_libraries(Gaze PRIVATE "-framework OpenGL")
    target_link_libraries(Gaze PRIVATE "-framework GLUT")
else ()
endif (WIN32)

target_precompile_headers(${PROJECT_NAME} PRIVATE "Source/GazePCH.h")
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog glfw)


