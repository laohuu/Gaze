set(Box2D_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/Box2D)
add_subdirectory(${Box2D_SOURCE_DIR_}/src)
target_include_directories(box2d PUBLIC $<BUILD_INTERFACE:${Box2D_SOURCE_DIR_}>)
