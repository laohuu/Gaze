file(GLOB entt_sources CONFIGURE_DEPENDS  "${CMAKE_CURRENT_SOURCE_DIR}/entt/*.hpp")
add_library(entt INTERFACE ${entt_sources})
target_include_directories(entt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/entt)