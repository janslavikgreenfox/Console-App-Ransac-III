# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(MySolution)

# Define build types explicitly
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Build types" FORCE)

# Add subdirectories for projects
add_subdirectory(StaticLibrary)
add_subdirectory(Executable)
#add_subdirectory(UnitTest)