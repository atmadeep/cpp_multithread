# Mandatory setup

1. Create a python3 virtual environment in the source directory.
2. Activate the virtual environemt (e.g. source path_to_venv/bin/activate)

---

# Building the standalone binary and unit tests

### Building the binary

```bash
cd src/
g++ -std=c++14 -pthread -o image_pipeline multithread_image_processing.cc `pkg-config --cflags --libs opencv4`
./image_pipeline
```

### Building the tests

Currently, support for building the gtest file with CMake is not added.

```bash
cd src/
g++ -std=c++14 -pthread -o image_pipeline_test image_processing_gtest.cc `pkg-config --cflags --libs opencv4` /usr/lib/x86_64-linux-gnu/libgtest.a 
./image_pipeline_test
```

# Building the python binding

```bash
mkdir build && cd build/
cmake -DBUILD_PYTHON_MODULE=ON ../
make

cd ..
python3 setup.py bdist_wheel
pip install dist/image_pipeline*.whl
```

This will install the wheel file in your virtual environment.
