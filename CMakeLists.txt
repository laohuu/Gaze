cmake_minimum_required(VERSION 3.23)
project(Gaze_Engine VERSION 0.1.0)


if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP") # enable parallel compilation
endif()

add_subdirectory(Gaze)
add_subdirectory(ScriptCore)
add_subdirectory(Editor/SandboxProject)
add_subdirectory(Sandbox)
add_subdirectory(Editor)