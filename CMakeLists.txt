cmake_minimum_required(VERSION 3.10)
project(image_pipeline_binding)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Enable threading
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Use pkg-config to get OpenCV flags and libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV4 REQUIRED opencv4)

# Include directories for OpenCV
include_directories(${OPENCV4_INCLUDE_DIRS})

# Add other necessary compile options from pkg-config
add_compile_options(${OPENCV4_CFLAGS_OTHER})

# Option to build Python module or regular C++ binary
option(BUILD_PYTHON_MODULE "Build Python module using pybind11" OFF)

# Create a regular C++ binary
add_executable(image_pipeline_cc src/multithread_image_processing.cc)

# Link OpenCV and pthread libraries to the executable
target_link_libraries(image_pipeline_cc PRIVATE ${OPENCV4_LIBRARIES} Threads::Threads)

if(BUILD_PYTHON_MODULE)
    message(STATUS "CMAKE : building python binding for image_pipeline")
    # Find pybind11
    find_package(pybind11 REQUIRED)
    
    # Create a Python module using pybind11
    pybind11_add_module(image_pipeline src/multithread_image_processing.cc)

    # Link OpenCV and pthread libraries to the Python module
    target_link_libraries(image_pipeline PRIVATE ${OPENCV4_LIBRARIES} Threads::Threads)
    target_compile_definitions(image_pipeline PRIVATE -DBUILD_PYTHON_MODULE=1)
endif()
