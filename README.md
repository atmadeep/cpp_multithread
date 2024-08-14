# Mandatory setup

1. Create a python3 virtual environment in the source directory.
2. Activate the virtual environemt (e.g. source path_to_venv/bin/activate)
3. Install `pytest`
   1. ```bash
      python3 -m pip install pytest
      ```

---

# Building

```bash
mkdir build && cd build
cmake -DBUILD_PYTHON_MODULE=ON ..
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
