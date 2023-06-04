set(ImGuizmo_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo)

file(GLOB ImGuizmo_sources CONFIGURE_DEPENDS "${ImGuizmo_SOURCE_DIR_}/ImGuizmo.cpp")
file(GLOB ImGuizmo_impl CONFIGURE_DEPENDS
        "${ImGuizmo_SOURCE_DIR_}/ImGuizmo.h"
        )

add_library(ImGuizmo STATIC ${ImGuizmo_sources} ${ImGuizmo_impl})

#target_compile_options(ImGuizmo PRIVATE "/std:c++17")
target_include_directories(ImGuizmo PUBLIC $<BUILD_INTERFACE:${ImGuizmo_SOURCE_DIR_}>)
target_link_libraries(ImGuizmo PUBLIC imgui)
