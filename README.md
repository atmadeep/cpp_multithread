# Mandatory setup

1. Create a python3 virtual environment in the source directory.
   1. ```bash
      python3 -m venv venv_1
      ```
2. Activate the virtual environment.
   1. ```bash
      source venv_1/bin/activate
      ```
3. Install required packages.
   1. ```bash
      python3 -m pip install -r requirements.txt
      ```

---

# Building

- To build all the binaries for the project

```bash
mkdir build && cd build
cmake -DBUILD_PYTHON_MODULE=ON --build ..
make all
```

- Install the python module
  - Change into project root directory
  - ```bash
    python3 setup.py install
    ```

    - This will install the python module in your environment

# Testing

- Run gtests

  - ```bash
    gtester bin/image_pipeline_test
    ```
- Run python tests

  - ```bash
    pytest bin
    ```

# Running the code

- To run the C++ binary

  - ```bash
    cd build/bin
    ./image_pipeline_app
    ```
- To run the python module package:

  - ```bash
    python3 bin/run_image_pipeline.py
    ```

# Profiling the app and pipeline

- Build and run the C++ binary with time profiling support:
- Only profiling support in C++ source is added with this option. You cannot build the profiling enabled binary as an installable module for python, as it will add to the overhead, and impact the profiling done in python
- ```bash
  cmake -DENABLE_PROFILING=ON --build ../
  bin/image_pipeline_app
  ```
- This will give you the `throughput` and `latency` of the pipleine and the `processImage()` function seperately. This is done in order to be able to track how much the optimizations are actually performing with respect to processing algorithm.
- C++ binary has been profile using heaptrack.
- ```bash
  heaptrack bin/image_pipeline_app
  heaptrack_gui heaptrack_image_pipeline.*
  ```
- A copy of the generated profile is available in `./profile_data` and can be visualised using `heaptrack_gui`. This app can be  installed using `sudo apt install heaptrack-gui`
- ```bash
  cd profile_data
  heaptrack_gui heaptrack_image_pipeline.*
  ```

  - A call graph is also added (see `profile_data/output.pdf`) for more. It's generated using `google-perfools`.
- To profile the python pipeline:
- ```bash
      python3 run_image_pipeline.py -p 1
      # visualize the pstats file
      snakeviz profile_output.pstats
  ```




- The profiling here has been done using `cProfile` and the functions run in parallel.

