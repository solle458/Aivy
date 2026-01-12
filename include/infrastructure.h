#ifndef AIVY_INFRASTRUCTURE_H
#define AIVY_INFRASTRUCTURE_H

#include <string>
#include <vector>
#include <memory>

namespace aivy {

/**
 * @brief Infrastructure services provided by C++ host to Python guest
 * 
 * This class provides OS-level and system-level functionality that
 * Python scripts can access through the API bindings.
 */
class Infrastructure {
public:
    /**
     * @brief Resolve a safe file path
     * @param relative_path Relative path to resolve
     * @return Absolute, validated path or empty string if invalid
     */
    static std::string resolveSafePath(const std::string& relative_path);

    /**
     * @brief Save data to a file safely
     * @param path File path (will be validated)
     * @param data Data to save
     * @return true if save succeeded, false otherwise
     */
    static bool saveData(const std::string& path, const std::string& data);

    /**
     * @brief Load data from a file safely
     * @param path File path (will be validated)
     * @return File contents or empty string if failed
     */
    static std::string loadData(const std::string& path);

    /**
     * @brief Get application data directory
     * @return Path to application data directory
     */
    static std::string getDataDirectory();

    /**
     * @brief List files in a directory
     * @param directory_path Directory to list
     * @return Vector of file paths
     */
    static std::vector<std::string> listFiles(const std::string& directory_path);

    /**
     * @brief Log a message from Python
     * @param level Log level (INFO, WARNING, ERROR)
     * @param message Message to log
     */
    static void log(const std::string& level, const std::string& message);
};

} // namespace aivy

#endif // AIVY_INFRASTRUCTURE_H
