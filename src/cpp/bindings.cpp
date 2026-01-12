#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "infrastructure.h"

namespace py = pybind11;

/**
 * @brief Python bindings for Aivy infrastructure API
 * 
 * This module exposes C++ infrastructure functions to Python scripts.
 * Python guest scripts can import this module to access host services.
 */
PYBIND11_MODULE(aivy_api, m) {
    m.doc() = "Aivy Infrastructure API - C++ host services for Python guest scripts";

    // Infrastructure class
    py::class_<aivy::Infrastructure>(m, "Infrastructure")
        .def_static("resolve_safe_path", &aivy::Infrastructure::resolveSafePath,
                   py::arg("relative_path"),
                   "Resolve a safe file path within the data directory")
        .def_static("save_data", &aivy::Infrastructure::saveData,
                   py::arg("path"),
                   py::arg("data"),
                   "Save data to a file (path will be validated for security)")
        .def_static("load_data", &aivy::Infrastructure::loadData,
                   py::arg("path"),
                   "Load data from a file (path will be validated for security)")
        .def_static("get_data_directory", &aivy::Infrastructure::getDataDirectory,
                   "Get the application data directory path")
        .def_static("list_files", &aivy::Infrastructure::listFiles,
                   py::arg("directory_path"),
                   "List files in a directory")
        .def_static("log", &aivy::Infrastructure::log,
                   py::arg("level"),
                   py::arg("message"),
                   "Log a message (level: INFO, WARNING, ERROR)");
}
