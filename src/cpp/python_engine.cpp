#include "python_engine.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace aivy {

PythonEngine::PythonEngine() : initialized_(false) {}

PythonEngine::~PythonEngine() {
    if (initialized_) {
        guard_.reset();
        initialized_ = false;
    }
}

bool PythonEngine::initialize() {
    if (initialized_) {
        std::cerr << "PythonEngine already initialized" << std::endl;
        return true;
    }

    try {
        guard_ = std::make_unique<py::scoped_interpreter>();
        
        // Add current directory to Python path
        py::module_ sys = py::module_::import("sys");
        py::list path = sys.attr("path");
        path.append(".");
        path.append("./src/python");
        
        initialized_ = true;
        std::cout << "Python interpreter initialized successfully" << std::endl;
        return true;
    } catch (const py::error_already_set& e) {
        std::cerr << "Failed to initialize Python interpreter: " << e.what() << std::endl;
        return false;
    }
}

bool PythonEngine::executeScript(const std::string& script_path) {
    if (!initialized_) {
        std::cerr << "PythonEngine not initialized" << std::endl;
        return false;
    }

    try {
        // Read the script file
        std::ifstream file(script_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open script: " << script_path << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string code = buffer.str();
        file.close();

        // Execute the code
        py::exec(code);
        std::cout << "Script executed successfully: " << script_path << std::endl;
        return true;
    } catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
        return false;
    }
}

bool PythonEngine::executeCode(const std::string& code) {
    if (!initialized_) {
        std::cerr << "PythonEngine not initialized" << std::endl;
        return false;
    }

    try {
        py::exec(code);
        return true;
    } catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
        return false;
    }
}

py::object PythonEngine::callFunction(const std::string& module_name,
                                      const std::string& function_name,
                                      const py::args& args) {
    if (!initialized_) {
        throw std::runtime_error("PythonEngine not initialized");
    }

    try {
        py::module_ module = py::module_::import(module_name.c_str());
        py::object func = module.attr(function_name.c_str());
        return func(*args);
    } catch (const py::error_already_set& e) {
        std::cerr << "Python error calling " << module_name << "." << function_name 
                  << ": " << e.what() << std::endl;
        throw;
    }
}

} // namespace aivy
