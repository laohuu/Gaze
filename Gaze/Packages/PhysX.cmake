file(GLOB PhysX_HEADS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/PhysX/include/*.h")
add_library(PhysX INTERFACE ${PhysX_HEADS})
target_include_directories(PhysX INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/PhysX/include)