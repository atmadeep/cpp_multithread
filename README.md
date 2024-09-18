# 🚀 Planned updates

As I'm working on becoming proficient in C++ with various ML and CV frameworks, I plan to scale this project as a real-time learning experience for everyone. Below are the planned updates:

- 🖥️ Working with GPU acceleration (preferably in Docker over native)
- 🔍 Replacing grayscale conversion with something more complex (object detection/segmentation/pose estimation + tracking) and scaling to use max threads
- 📊 Working with more performance measurement tools

# 🛠️ Mandatory setup

1. Create a Python3 virtual environment in the source directory:
   ```bash
   python3 -m venv venv_1
   ```

2. Activate the virtual environment:
   ```bash
   source venv_1/bin/activate
   ```

3. Install required packages:
   ```bash
   python3 -m pip install -r requirements.txt
   ```

---

# 🏗️ Building

To build all the binaries for the project:

```bash
mkdir build && cd build
cmake -DBUILD_PYTHON_MODULE=ON --build ..
make all
```

Install the Python module:
- Change into project root directory
- ```bash
  python3 setup.py install
  ```
  This will install the Python module in your environment.

# 🧪 Testing

- Run gtests:
  ```bash
  gtester bin/image_pipeline_test
  ```

- Run Python tests:
  ```bash
  pytest bin
  ```

# 🏃‍♂️ Running the code

- To run the C++ binary:
  ```bash
  cd build/bin
  ./image_pipeline_app
  ```

- To run the Python module package:
  ```bash
  python3 bin/run_image_pipeline.py
  ```

# 📈 Profiling the app and pipeline

## C++ Profiling

1. Build and run the C++ binary with time profiling support:
   ```bash
   cmake -DENABLE_PROFILING=ON --build ../
   bin/image_pipeline_app
   ```
   - This will give you the `throughput` and `latency` of the pipeline and the `processImage()` function separately.
   - Note: You cannot build the profiling-enabled binary as an installable module for Python, as it will add overhead and impact the profiling done in Python.

2. Profile using heaptrack:
   ```bash
   heaptrack bin/image_pipeline_app
   heaptrack_gui heaptrack_image_pipeline.*
   ```
   - A copy of the generated profile is available in `./profile_data` and can be visualized using `heaptrack_gui`.
   - Install heaptrack_gui: `sudo apt install heaptrack-gui`
   - To view the profile:
     ```bash
     cd profile_data
     heaptrack_gui heaptrack_image_pipeline.*
     ```
   - A call graph is also added (see `profile_data/output.pdf`). It's generated using `google-perftools`.

## Python Profiling

To profile the Python pipeline:
```bash
python3 run_image_pipeline.py -p 1
# visualize the pstats file
snakeviz profile_output.pstats
```
- The profiling here has been done using `cProfile` and the functions run in parallel.
