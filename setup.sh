#!/bin/bash

# Aivy Setup Script
# This script automates the initial setup and build process

set -e

echo "======================================"
echo "  Aivy Setup and Build Script"
echo "======================================"
echo ""

# Check for required tools
echo "Checking prerequisites..."

if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake is not installed"
    echo "Please install CMake (version 3.12 or higher)"
    exit 1
fi

if ! command -v git &> /dev/null; then
    echo "ERROR: Git is not installed"
    exit 1
fi

if ! command -v python3 &> /dev/null; then
    echo "ERROR: Python 3 is not installed"
    exit 1
fi

echo "✓ All prerequisites found"
echo ""

# Clone pybind11 if not present
if [ ! -d "external/pybind11" ]; then
    echo "Cloning pybind11..."
    mkdir -p external
    cd external
    git clone https://github.com/pybind/pybind11.git
    cd ..
    echo "✓ pybind11 cloned successfully"
else
    echo "✓ pybind11 already present"
fi
echo ""

# Create build directory
echo "Creating build directory..."
mkdir -p build
echo "✓ Build directory created"
echo ""

# Configure with CMake
echo "Configuring project with CMake..."
cd build
cmake ..
echo "✓ Configuration complete"
echo ""

# Build
echo "Building project..."
cmake --build . --config Release
echo "✓ Build complete"
echo ""

# Create data directory
cd ..
mkdir -p data
echo "✓ Data directory created"
echo ""

echo "======================================"
echo "  Setup Complete!"
echo "======================================"
echo ""
echo "To run Aivy:"
echo "  ./build/bin/aivy"
echo ""
echo "To run with a script:"
echo "  ./build/bin/aivy examples/ml_example.py"
echo ""
echo "To use the Python API:"
echo "  export PYTHONPATH=\"\${PYTHONPATH}:\$(pwd)/build/lib\""
echo "  python3 -c \"import aivy_api; aivy_api.Infrastructure.log('INFO', 'Test')\""
echo ""
