#ifndef AIVY_PYTHON_ENGINE_H
#define AIVY_PYTHON_ENGINE_H

#include <pybind11/embed.h>
#include <string>
#include <memory>

namespace py = pybind11;

namespace aivy {

/**
 * @brief Manages the embedded Python interpreter
 * 
 * This class handles:
 * - Python interpreter initialization and finalization
 * - Script execution
 * - Python module loading
 * - Communication between C++ host and Python guest
 */
class PythonEngine {
public:
    PythonEngine();
    ~PythonEngine();

    // Prevent copying
    PythonEngine(const PythonEngine&) = delete;
    PythonEngine& operator=(const PythonEngine&) = delete;

    /**
     * @brief Initialize the Python interpreter
     * @return true if initialization succeeded, false otherwise
     */
    bool initialize();

    /**
     * @brief Execute a Python script file
     * @param script_path Path to the Python script
     * @return true if execution succeeded, false otherwise
     */
    bool executeScript(const std::string& script_path);

    /**
     * @brief Execute Python code from a string
     * @param code Python code to execute
     * @return true if execution succeeded, false otherwise
     */
    bool executeCode(const std::string& code);

    /**
     * @brief Call a Python function
     * @param module_name Name of the Python module
     * @param function_name Name of the function to call
     * @param args Arguments to pass to the function
     * @return Result of the function call
     */
    py::object callFunction(const std::string& module_name, 
                           const std::string& function_name,
                           const py::args& args = py::tuple());

    /**
     * @brief Check if the engine is initialized
     * @return true if initialized, false otherwise
     */
    bool isInitialized() const { return initialized_; }

private:
    bool initialized_;
    std::unique_ptr<py::scoped_interpreter> guard_;
};

} // namespace aivy

#endif // AIVY_PYTHON_ENGINE_H
