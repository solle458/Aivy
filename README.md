# Aivy
Dynamic ML Platform (for my research)

## Architecture

Aivy is a hybrid C++/Python platform for machine learning research, featuring:

### Host (C++) - System Controller
- Application lifecycle management (startup/shutdown, memory management)
- Embedded Python interpreter control
- Infrastructure services:
  - Database connections
  - Safe file path resolution (security)
  - OS-level operations
  - API exposure to Python

### Guest (Python) - Extension Functions
- User-uploaded ML scripts
- Called from C++ host to execute ML tasks (training, inference)
- Accesses host services through provided C++ API

### Technology Stack
- **C++17**: Host system implementation
- **Python 3**: Guest script runtime
- **pybind11**: C++/Python bindings

## Project Structure

```
Aivy/
├── CMakeLists.txt          # Build configuration
├── include/                # C++ header files
│   ├── python_engine.h     # Python interpreter management
│   └── infrastructure.h    # Infrastructure services
├── src/
│   ├── cpp/                # C++ implementation
│   │   ├── main.cpp        # Main application entry
│   │   ├── python_engine.cpp
│   │   ├── infrastructure.cpp
│   │   └── bindings.cpp    # pybind11 bindings
│   └── python/             # Python modules
├── examples/               # Example scripts
│   └── ml_example.py       # Example ML guest script
├── tests/                  # Tests
│   ├── cpp/                # C++ tests
│   └── python/             # Python tests
├── build/                  # Build artifacts (gitignored)
└── data/                   # Application data directory
```

## Prerequisites

### Required
- **CMake** >= 3.12
- **C++ Compiler** with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)
- **Python 3** (3.7 or higher) with development headers
- **Git** (for cloning pybind11)

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake python3-dev python3-pip git
```

### macOS
```bash
brew install cmake python@3 git
```

### Windows
- Install Visual Studio 2017 or later with C++ tools
- Install CMake from https://cmake.org/download/
- Install Python 3 from https://www.python.org/downloads/

## Building

### 1. Clone pybind11

```bash
mkdir -p external
cd external
git clone https://github.com/pybind/pybind11.git
cd ..
```

### 2. Build the Project

```bash
# Create build directory
mkdir -p build
cd build

# Configure
cmake ..

# Build
cmake --build . --config Release

# Optional: Install
sudo cmake --install .
```

### 3. Verify Build

The build should produce:
- `build/bin/aivy` - Main executable
- `build/lib/aivy_api.*.so` (or `.pyd` on Windows) - Python module

## Running

### Run with embedded example

```bash
./build/bin/aivy
```

This will execute the built-in example demonstrating the C++/Python API.

### Run with a Python script

```bash
./build/bin/aivy examples/ml_example.py
```

### Use the Python API module

```bash
# Add the library path to Python
export PYTHONPATH="${PYTHONPATH}:$(pwd)/build/lib"

# Now you can import aivy_api in any Python script
python3 -c "import aivy_api; aivy_api.Infrastructure.log('INFO', 'Test')"
```

## Python API Reference

The `aivy_api` module provides the following infrastructure services:

### Infrastructure Class

```python
import aivy_api

# Resolve safe file path
path = aivy_api.Infrastructure.resolve_safe_path("myfile.txt")

# Save data (with automatic security validation)
aivy_api.Infrastructure.save_data("models/model.pkl", data)

# Load data
data = aivy_api.Infrastructure.load_data("models/model.pkl")

# Get data directory
data_dir = aivy_api.Infrastructure.get_data_directory()

# List files in directory
files = aivy_api.Infrastructure.list_files("models")

# Log messages
aivy_api.Infrastructure.log("INFO", "Message")
aivy_api.Infrastructure.log("WARNING", "Warning message")
aivy_api.Infrastructure.log("ERROR", "Error message")
```

## Writing Guest Scripts

Python guest scripts have access to the infrastructure API:

```python
import aivy_api

def my_ml_task():
    # Log activity
    aivy_api.Infrastructure.log("INFO", "Starting ML task")
    
    # Load training data
    data = aivy_api.Infrastructure.load_data("training_data.csv")
    
    # Train model (your code here)
    model = train_my_model(data)
    
    # Save model
    aivy_api.Infrastructure.save_data("models/my_model.pkl", model)
    
    aivy_api.Infrastructure.log("INFO", "Task completed")

if __name__ == "__main__":
    my_ml_task()
```

## Security Features

- **Path validation**: All file operations validate paths to prevent directory traversal attacks
- **Sandboxed data directory**: Python scripts can only access files within the `data/` directory
- **Controlled API**: Python scripts only access OS features through the controlled C++ API

## Development

### Adding New Infrastructure Services

1. Add function declaration in `include/infrastructure.h`
2. Implement in `src/cpp/infrastructure.cpp`
3. Add Python binding in `src/cpp/bindings.cpp`
4. Rebuild the project

### Testing

```bash
# Build tests
cmake --build build --target tests

# Run tests
cd build
ctest
```

## License

See LICENSE file for details.

## Contributing

This is a research project. Please contact the maintainer before contributing.
