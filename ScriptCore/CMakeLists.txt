cmake_minimum_required(VERSION 3.23)
project(ScriptCore VERSION 0.1.0 LANGUAGES CSharp)

file(GLOB_RECURSE SOURCE_FILES "Source/**.cs")
file(GLOB_RECURSE PROPERTIES_FILES "Properties/**.cs")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${PROPERTIES_FILES})

# Set the .NET Framework version for the executable.
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")