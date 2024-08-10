cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 14)
project(image_pipeline)

find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(pybind11)

pybind11_add_module(image_pipeline src/multithread_image_processing.cc)
target_link_libraries(image_pipeline PRIVATE ${OpenCV_LIBS} )

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(image_pipeline PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})