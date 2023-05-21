cmake_minimum_required(VERSION 3.25)
project(glad)

add_library(${PROJECT_NAME} src/glad.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )