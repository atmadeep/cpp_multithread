cmake_minimum_required(VERSION 3.10)
project(image_pipeline_binding)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Adding subdirectories
# Enable threading
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Use pkg-config to get OpenCV flags and libraries
find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)
pkg_check_modules(OPENCV4 REQUIRED opencv4)

# Include directories for OpenCV
include_directories(${OPENCV4_INCLUDE_DIRS})

# Add other necessary compile options from pkg-config
add_compile_options(${OPENCV4_CFLAGS_OTHER})

# Option to build Python module or regular C++ binary
option(BUILD_PYTHON_MODULE "Build Python module using pybind11" OFF)
add_subdirectory(src)
add_subdirectory(src/tests/cxx)
add_subdirectory(python_bindings)

message(STATUS "Copying image_pipeline_test.py to build/bin directory")
file(COPY ${CMAKE_SOURCE_DIR}/src/tests/python/test_image_pipeline.py DESTINATION ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Copying run_image_pipeline.py to build/bin directory")
file(COPY ${CMAKE_SOURCE_DIR}/src/python/run_image_pipeline.py DESTINATION ${CMAKE_BINARY_DIR}/bin)