cmake_minimum_required(VERSION 3.23)
#如果没有指定则设置默认编译方式
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    #在命令行中输出message里的信息
    message("Setting build type to 'Debug' as none was specified.")
    #不管CACHE里有没有设置过CMAKE_BUILD_TYPE这个变量，都强制赋值这个值为RelWithDebInfo
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

    # 当使用cmake-gui的时候，设置构建级别的四个可选项
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif ()

project(Gaze VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(Packages)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC opengl32)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Packages/spdlog/include
        ${PROJECT_SOURCE_DIR}/Packages/stb
        ${PROJECT_SOURCE_DIR}/Packages/GLFW/include
        ${PROJECT_SOURCE_DIR}/Packages/glm
        ${PROJECT_SOURCE_DIR}/Packages/entt/include
        ${PROJECT_SOURCE_DIR}/Packages/yaml-cpp/include
        ${PROJECT_SOURCE_DIR}/Source
        )

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Source/GazePCH.h")

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

if (WIN32)
#    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
elseif (APPLE)
    #    target_link_libraries(Gaze PRIVATE "-framework OpenGL")
    #    target_link_libraries(Gaze PRIVATE "-framework GLUT")
else ()
endif (WIN32)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_RELEASE)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_REL_WITH_DEB_INFO)
elseif (CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_MIN_SIZE_REL)
endif ()


