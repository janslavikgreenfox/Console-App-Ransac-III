# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(MySolution)

# Define build types explicitly
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Build types" FORCE)

# Defines the global configuration
set(CMAKE_CXX_STANDARD 17)  # Or 20 if your project uses C++20 features
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add subdirectories for projects
add_subdirectory(StaticLibrary)
add_subdirectory(Executable)
#add_subdirectory(UnitTest)