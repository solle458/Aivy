cmake_minimum_required(VERSION 3.12)
project(Aivy VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find Python
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Python3 found: ${Python3_EXECUTABLE}")
message(STATUS "Python3 include dirs: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python3 libraries: ${Python3_LIBRARIES}")

# Add pybind11
add_subdirectory(external/pybind11)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Python3_INCLUDE_DIRS}
)

# Source files
set(AIVY_SOURCES
    src/cpp/main.cpp
    src/cpp/python_engine.cpp
    src/cpp/infrastructure.cpp
)

# Create main executable
add_executable(aivy ${AIVY_SOURCES})
target_link_libraries(aivy PRIVATE Python3::Python pybind11::embed)

# Create Python module for API bindings
pybind11_add_module(aivy_api src/cpp/bindings.cpp src/cpp/infrastructure.cpp)

# Installation
install(TARGETS aivy DESTINATION bin)
install(TARGETS aivy_api LIBRARY DESTINATION ${Python3_SITELIB})
