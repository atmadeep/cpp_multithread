set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
enable_testing()
# Use pkg-config to get OpenCV flags and libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV4 REQUIRED opencv4)
include_directories(${OPENCV4_INCLUDE_DIRS})
add_compile_options(${OPENCV4_CFLAGS_OTHER})

add_executable(image_pipeline_app cxx/multithread_image_processing.cc)

target_link_libraries(image_pipeline_app PRIVATE ${OPENCV4_LIBRARIES} Threads::Threads)