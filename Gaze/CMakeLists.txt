cmake_minimum_required(VERSION 3.23)
project(Gaze VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(Packages)
add_compile_definitions(GZ_DEBUG)

set(SOURCES
        Source/Core/Application.cpp
        Source/Core/Application.h
        Source/Core/Log.cpp
        Source/Core/Log.h
        Source/Core/Core.h
        Source/Core/EntryPoint.h
        Source/Gaze.h
        Source/GazePCH.cpp
        Source/GazePCH.h)

include_directories(Source)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PUBLIC "Source/GazePCH.h")
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)