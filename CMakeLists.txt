project(DeltaRayXLCE_Emulator)
cmake_minimum_required(VERSION 3.2)

# Binding
file(GLOB_RECURSE DeltaRayXLCE_Emulator_Binding_Sources Binding/*.hxx)

set_property(SOURCE ${DeltaRayXLCE_Emulator_Binding_Sources} PROPERTY LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 23)

add_library(DeltaRayXLCE_Emulator_Binding SHARED ${DeltaRayXLCE_Emulator_Binding_Sources} Include/emulator/binding)
target_include_directories(DeltaRayXLCE_Emulator_Binding PUBLIC Include)

# Development
file(GLOB_RECURSE DeltaRayXLCE_Emulator_Development_Sources Private/Development/*.cxx Private/Development/*.hxx)
add_executable(DeltaRayXLCE_Emulator_Development ${DeltaRayXLCE_Emulator_Development_Sources})