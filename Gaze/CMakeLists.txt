cmake_minimum_required(VERSION 3.23)
project(Gaze VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(Packages)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

if (WIN32)
elseif (UNIX AND NOT APPLE)
elseif (APPLE)
    #    set(GLFW_LINK Lib/GLFW/lib-arm64/libglfw.3.dylib)
    #    link_libraries(${GLFW_LINK})
    #
    #    target_link_libraries(Gaze PRIVATE "-framework OpenGL")
    #    target_link_libraries(Gaze PRIVATE "-framework GLUT")
else ()
endif (WIN32)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC opengl32)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Packages/spdlog/include
        ${PROJECT_SOURCE_DIR}/Packages/GLFW/include
        ${PROJECT_SOURCE_DIR}/Source
        )

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Source/GazePCH.h")

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)
target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_DEBUG)


