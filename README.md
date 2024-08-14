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
cmake -DBUILD_PYTHON_MODULE=ON ..
make
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
