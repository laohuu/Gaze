set(third_party_folder "Packages")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if (NOT TARGET imgui)
    include(imgui.cmake)
    set_target_properties(imgui PROPERTIES FOLDER ${third_party_folder}/imgui)
endif ()

if (NOT TARGET glm)
    add_subdirectory(glm)
    set_target_properties(glm PROPERTIES FOLDER ${third_party_folder}/glm)
endif ()

if (NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(GLFW)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/GLFW)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/GLFW)
endif ()

if (NOT TARGET spdlog)
    option(SPDLOG_BUILD_EXAMPLE "" OFF)
    option(SPDLOG_INSTALL "" OFF)
    add_subdirectory(spdlog)
    set_target_properties(spdlog PROPERTIES FOLDER ${third_party_folder}/spdlog)
endif ()

if (NOT TARGET stb)
    include(stb.cmake)
    set_target_properties(stb PROPERTIES FOLDER ${third_party_folder}/stb)
endif ()

if (NOT TARGET entt)
    include(entt.cmake)
    set_target_properties(entt PROPERTIES FOLDER ${third_party_folder}/entt)
endif ()

if (NOT TARGET glad)
    add_subdirectory(glad)
    set_target_properties(glad PROPERTIES FOLDER ${third_party_folder}/glad)
endif ()

if (NOT TARGET yaml-cpp)
    add_subdirectory(yaml-cpp)
    set_target_properties(yaml-cpp PROPERTIES FOLDER ${third_party_folder}/yaml-cpp)
endif ()

if (NOT TARGET msdf-atlas-gen)
    add_subdirectory(msdf-atlas-gen)
    set_target_properties(msdf-atlas-gen PROPERTIES FOLDER ${third_party_folder}/msdf-atlas-gen)
endif ()

if (NOT TARGET ImGuizmo)
    include(ImGuizmo.cmake)
    set_target_properties(ImGuizmo PROPERTIES FOLDER ${third_party_folder}/ImGuizmo)
endif ()

if (NOT TARGET box2d)
    include(box2d.cmake)
    set_target_properties(box2d PROPERTIES FOLDER ${third_party_folder}/Box2D)
endif ()

if (NOT TARGET filewatch)
    include(filewatch.cmake)
    set_target_properties(filewatch PROPERTIES FOLDER ${third_party_folder}/filewatch)
endif ()

if (NOT TARGET PhysX)
    include(PhysX.cmake)
    set_target_properties(PhysX PROPERTIES FOLDER ${third_party_folder}/PhysX)
endif ()


