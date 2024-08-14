# Find Python3 and Pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

if(BUILD_PYTHON_MODULE)
    message(STATUS "CMAKE : building python binding for image_pipeline")
    # Find pybind11
    find_package(pybind11 REQUIRED)
    
    # Create a Python module using pybind11
    pybind11_add_module(image_pipeline ../src/cxx/multithread_image_processing.cc)

    # Link OpenCV and pthread libraries to the Python module
    target_link_libraries(image_pipeline PRIVATE ${OPENCV4_LIBRARIES} Threads::Threads)
    target_compile_definitions(image_pipeline PRIVATE -DBUILD_PYTHON_MODULE=1)
endif()
