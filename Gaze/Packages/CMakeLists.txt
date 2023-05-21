set(third_party_folder "Packages")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if(NOT TARGET imgui)
   include(imgui.cmake)
   set_target_properties(imgui PROPERTIES FOLDER ${third_party_folder}/imgui)
endif()

if(NOT TARGET glm)
   add_subdirectory(glm)
   set_target_properties(glm PROPERTIES FOLDER ${third_party_folder}/glm)
endif()

if(NOT TARGET glfw)
   option(GLFW_BUILD_EXAMPLES "" OFF)
   option(GLFW_BUILD_TESTS "" OFF)
   option(GLFW_BUILD_DOCS "" OFF)
   option(GLFW_INSTALL "" OFF)
   add_subdirectory(GLFW)
   set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/GLFW)
   set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/GLFW)
endif()

if(NOT TARGET spdlog)
   option(SPDLOG_BUILD_EXAMPLE "" OFF)
   option(SPDLOG_INSTALL "" OFF)
   add_subdirectory(spdlog)
   set_target_properties(spdlog PROPERTIES FOLDER ${third_party_folder}/spdlog)
endif()

if(NOT TARGET glad)
   add_subdirectory(glad)
   set_target_properties(glad PROPERTIES FOLDER ${third_party_folder}/glad)
endif()

