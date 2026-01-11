#include "infrastructure.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;

namespace aivy {

std::string Infrastructure::resolveSafePath(const std::string& relative_path) {
    try {
        fs::path base_path = fs::current_path() / "data";
        
        // Create base path if it doesn't exist
        if (!fs::exists(base_path)) {
            fs::create_directories(base_path);
        }
        
        // Resolve the full path (without requiring the file to exist)
        fs::path full_path = base_path / relative_path;
        
        // Normalize the path to handle .. and . components
        full_path = full_path.lexically_normal();
        
        // Get canonical base path
        auto canonical_base = fs::canonical(base_path);
        
        // Check if the normalized path starts with the base path
        // This prevents directory traversal attacks
        auto full_path_str = full_path.string();
        auto base_path_str = canonical_base.string();
        
        if (full_path_str.find(base_path_str) == 0) {
            return full_path.string();
        } else {
            std::cerr << "Path traversal attempt detected: " << relative_path << std::endl;
            return "";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Path resolution error: " << e.what() << std::endl;
        return "";
    }
}

bool Infrastructure::saveData(const std::string& path, const std::string& data) {
    std::string safe_path = resolveSafePath(path);
    if (safe_path.empty()) {
        return false;
    }

    try {
        // Create parent directories if they don't exist
        fs::path file_path(safe_path);
        fs::create_directories(file_path.parent_path());

        std::ofstream file(safe_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << safe_path << std::endl;
            return false;
        }

        file << data;
        file.close();
        std::cout << "Data saved to: " << safe_path << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << std::endl;
        return false;
    }
}

std::string Infrastructure::loadData(const std::string& path) {
    std::string safe_path = resolveSafePath(path);
    if (safe_path.empty()) {
        return "";
    }

    try {
        std::ifstream file(safe_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for reading: " << safe_path << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return "";
    }
}

std::string Infrastructure::getDataDirectory() {
    try {
        fs::path data_path = fs::current_path() / "data";
        fs::create_directories(data_path);
        return data_path.string();
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error getting data directory: " << e.what() << std::endl;
        return "";
    }
}

std::vector<std::string> Infrastructure::listFiles(const std::string& directory_path) {
    std::vector<std::string> files;
    std::string safe_path = resolveSafePath(directory_path);
    
    if (safe_path.empty()) {
        return files;
    }

    try {
        for (const auto& entry : fs::directory_iterator(safe_path)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error listing files: " << e.what() << std::endl;
    }

    return files;
}

void Infrastructure::log(const std::string& level, const std::string& message) {
    // Get current timestamp
    std::time_t now = std::time(nullptr);
    char timestamp[64];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    std::cout << "[" << timestamp << "] [" << level << "] " << message << std::endl;
}

} // namespace aivy
