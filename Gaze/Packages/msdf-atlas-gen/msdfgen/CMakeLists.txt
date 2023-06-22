
cmake_minimum_required(VERSION 3.15)
include(cmake/version.cmake)

option(MSDFGEN_DYNAMIC_RUNTIME "Link dynamic runtime library instead of static" ON)
set(MSDFGEN_DYNAMIC_RUNTIME ON)

if (MSDFGEN_DYNAMIC_RUNTIME)
    set(MSDFGEN_MSVC_RUNTIME "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else ()
    set(MSDFGEN_MSVC_RUNTIME "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

# Version is specified in vcpkg.json
project(msdfgen VERSION ${MSDFGEN_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MSDFGEN_CORE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "core/*.h" "core/*.hpp")
file(GLOB_RECURSE MSDFGEN_CORE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "core/*.cpp")
file(GLOB_RECURSE MSDFGEN_EXT_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "ext/*.h" "ext/*.hpp" "include/*.h")
file(GLOB_RECURSE MSDFGEN_EXT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "ext/*.cpp" "lib/*.cpp")

add_subdirectory(freetype)

# Core library
add_library(msdfgen-core "${CMAKE_CURRENT_SOURCE_DIR}/msdfgen.h" ${MSDFGEN_CORE_HEADERS} ${MSDFGEN_CORE_SOURCES})
add_library(msdfgen::msdfgen-core ALIAS msdfgen-core)

set_target_properties(msdfgen-core PROPERTIES PUBLIC_HEADER "${MSDFGEN_CORE_HEADERS}")
set_property(TARGET msdfgen-core PROPERTY MSVC_RUNTIME_LIBRARY "${MSDFGEN_MSVC_RUNTIME}")
target_compile_definitions(msdfgen-core PRIVATE
        MSDFGEN_VERSION=${MSDFGEN_VERSION}
        MSDFGEN_VERSION_MAJOR=${MSDFGEN_VERSION_MAJOR}
        MSDFGEN_VERSION_MINOR=${MSDFGEN_VERSION_MINOR}
        MSDFGEN_VERSION_REVISION=${MSDFGEN_VERSION_REVISION}
        MSDFGEN_COPYRIGHT_YEAR=${MSDFGEN_COPYRIGHT_YEAR}
        )
target_include_directories(msdfgen-core INTERFACE
        $<INSTALL_INTERFACE:include/msdfgen>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        )

target_compile_features(msdfgen-core PUBLIC cxx_std_11)
target_compile_definitions(msdfgen-core PRIVATE MSDFGEN_USE_CPP11)
target_compile_definitions(msdfgen-core PRIVATE MSDFGEN_PUBLIC=)

add_library(msdfgen-ext "${CMAKE_CURRENT_SOURCE_DIR}/msdfgen-ext.h" ${MSDFGEN_EXT_HEADERS} ${MSDFGEN_EXT_SOURCES})
add_library(msdfgen::msdfgen-ext ALIAS msdfgen-ext)
set_target_properties(msdfgen-ext PROPERTIES PUBLIC_HEADER "${MSDFGEN_EXT_HEADERS}")
set_property(TARGET msdfgen-ext PROPERTY MSVC_RUNTIME_LIBRARY "${MSDFGEN_MSVC_RUNTIME}")
target_compile_definitions(msdfgen-ext INTERFACE MSDFGEN_EXTENSIONS)
target_link_libraries(msdfgen-ext PRIVATE freetype msdfgen::msdfgen-core)
target_include_directories(msdfgen-ext
        PUBLIC
        $<INSTALL_INTERFACE:include/msdfgen>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_compile_definitions(msdfgen-ext PRIVATE MSDFGEN_EXT_PUBLIC=)
target_compile_definitions(msdfgen-ext PUBLIC MSDFGEN_USE_LODEPNG)

add_library(msdfgen-full INTERFACE)
add_library(msdfgen::msdfgen ALIAS msdfgen-full)
target_link_libraries(msdfgen-full INTERFACE msdfgen::msdfgen-core msdfgen::msdfgen-ext)