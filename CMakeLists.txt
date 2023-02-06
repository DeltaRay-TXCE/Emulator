project(DeltaRayXLCE_Emulator)
cmake_minimum_required(VERSION 3.2)

file(GLOB_RECURSE DeltaRayXLCE_Emulator_SOURCES "Source/*.cxx" "Source/*.hxx" "Device/*.cxx" "Device/*.hxx")
add_executable(emulator ${DeltaRayXLCE_Emulator_SOURCES})