cmake_minimum_required(VERSION 3.23)
project(GazeEditor VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Gaze)

set(POST_BUILD_COMMANDS
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/Assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "${CMAKE_CURRENT_BINARY_DIR}/Assets"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/Configs/imgui.ini" "${CMAKE_CURRENT_BINARY_DIR}/imgui.ini"
        )

add_custom_command(TARGET ${PROJECT_NAME} ${POST_BUILD_COMMANDS})