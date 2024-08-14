# Enable testing
enable_testing()

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)
pkg_check_modules(OPENCV4 REQUIRED opencv4)
# Find GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${OPENCV4_INCLUDE_DIRS})
add_compile_options(${OPENCV4_CFLAGS_OTHER})
# Add the test executable
add_executable(image_pipeline_test image_processing_gtest.cc)

# Link libraries
target_link_libraries(image_pipeline_test ${OPENCV4_LIBRARIES} GTest::GTest GTest::Main Threads::Threads)
