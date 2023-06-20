file(GLOB filewatch_sources CONFIGURE_DEPENDS  "${CMAKE_CURRENT_SOURCE_DIR}/filewatch/*.h")
add_library(filewatch INTERFACE ${filewatch_sources})
target_include_directories(filewatch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/filewatch)