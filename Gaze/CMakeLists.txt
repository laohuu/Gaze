cmake_minimum_required(VERSION 3.23)
#如果没有指定则设置默认编译方式
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    #在命令行中输出message里的信息
    message("Setting build type to 'Debug' as none was specified.")
    #不管CACHE里有没有设置过CMAKE_BUILD_TYPE这个变量，都强制赋值这个值为RelWithDebInfo
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

    # 当使用cmake-gui的时候，设置构建级别的四个可选项
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif ()

project(Gaze VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(Packages)

file(GLOB_RECURSE HEADER_FILES "Source/*.h")
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

set(VK_SDK_PATH $ENV{VK_SDK_PATH})
set(VK_SDK_INCLUDE ${VK_SDK_PATH}/Include)
set(VK_SDK_LIB ${VK_SDK_PATH}/Lib/vulkan-1.lib)
set(VK_UTILS_LIB ${VK_SDK_PATH}/Lib/VkLayer_utils.lib)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(ShaderC_LIB ${VK_SDK_PATH}/Lib/shaderc_sharedd.lib)
    set(ShaderC_Utils_LIB ${VK_SDK_PATH}/Lib/shaderc_utild.lib)
    set(SPIRV_Cross_LIB ${VK_SDK_PATH}/Lib/spirv-cross-cored.lib)
    set(SPIRV_Cross_GLSL_LIB ${VK_SDK_PATH}/Lib/spirv-cross-glsld.lib)
    set(SPIRV_Tools_LIB ${VK_SDK_PATH}/Lib/SPIRV-Toolsd.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SPIRV_Tools_LIB})

    set(MONO_LIB ${PROJECT_SOURCE_DIR}/Packages/mono/lib/Debug/libmono-static-sgen.lib)
else ()
    set(ShaderC_LIB ${VK_SDK_PATH}/Lib/shaderc_shared.lib)
    set(ShaderC_Utils_LIB ${VK_SDK_PATH}/Lib/shaderc_util.lib)
    set(SPIRV_Cross_LIB ${VK_SDK_PATH}/Lib/spirv-cross-core.lib)
    set(SPIRV_Cross_GLSL_LIB ${VK_SDK_PATH}/Lib/spirv-cross-glsl.lib)

    set(MONO_LIB ${PROJECT_SOURCE_DIR}/Packages/mono/lib/Release/libmono-static-sgen.lib)
endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC ImGuizmo)
target_link_libraries(${PROJECT_NAME} PUBLIC opengl32)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC box2d)
target_link_libraries(${PROJECT_NAME} PUBLIC msdf-atlas-gen)
target_link_libraries(${PROJECT_NAME} PRIVATE PhysX)
target_link_libraries(${PROJECT_NAME} PRIVATE ${VK_SDK_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${VK_UTILS_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ShaderC_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ShaderC_Utils_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SPIRV_Cross_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SPIRV_Cross_GLSL_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MONO_LIB})

#Physics
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(PhysX_LIB_DIR ${PROJECT_SOURCE_DIR}/Packages/PhysX/lib/Debug)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(PhysX_LIB_DIR ${PROJECT_SOURCE_DIR}/Packages/PhysX/lib/Release)
    target_compile_definitions(${PROJECT_NAME} PUBLIC NDEBUG) # -- PhysX Requires This
else ()
    set(PhysX_LIB_DIR ${PROJECT_SOURCE_DIR}/Packages/PhysX/lib/Release)
    target_compile_definitions(${PROJECT_NAME} PUBLIC NDEBUG) # -- PhysX Requires This
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysX_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXCharacterKinematic_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXCommon_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXCooking_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXExtensions_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXFoundation_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXPvdSDK_static_64.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PhysX_LIB_DIR}/PhysXVehicle_static_64.lib)

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Source/GazePCH.h")

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Packages/spdlog/include
        ${PROJECT_SOURCE_DIR}/Packages/GLFW/include
        ${PROJECT_SOURCE_DIR}/Packages/glm
        ${PROJECT_SOURCE_DIR}/Packages/filewatch
        ${PROJECT_SOURCE_DIR}/Packages/entt/include
        ${PROJECT_SOURCE_DIR}/Packages/yaml-cpp/include
        ${PROJECT_SOURCE_DIR}/Packages/mono/include
        ${VK_SDK_INCLUDE}
        ${PROJECT_SOURCE_DIR}/Source
        )

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)
target_compile_definitions(${PROJECT_NAME} PUBLIC PX_PHYSX_STATIC_LIB)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE Ws2_32.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE Winmm.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE Version.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE Bcrypt.lib)
elseif (UNIX AND NOT APPLE)
elseif (APPLE)
    #    target_link_libraries(Gaze PRIVATE "-framework OpenGL")
    #    target_link_libraries(Gaze PRIVATE "-framework GLUT")
else ()
endif (WIN32)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_DEBUG)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_RELEASE)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_REL_WITH_DEB_INFO)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GZ_MIN_SIZE_REL)
endif ()


