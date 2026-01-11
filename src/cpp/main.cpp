#include "python_engine.h"
#include "infrastructure.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "==================================" << std::endl;
    std::cout << "    Aivy - Dynamic ML Platform    " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;

    // Create and initialize Python engine
    aivy::PythonEngine engine;
    
    if (!engine.initialize()) {
        std::cerr << "Failed to initialize Python engine" << std::endl;
        return 1;
    }

    // Setup data directory
    std::string data_dir = aivy::Infrastructure::getDataDirectory();
    std::cout << "Data directory: " << data_dir << std::endl;
    std::cout << std::endl;

    // Check if a script was provided as argument
    if (argc > 1) {
        std::string script_path = argv[1];
        std::cout << "Executing Python script: " << script_path << std::endl;
        
        if (!engine.executeScript(script_path)) {
            std::cerr << "Script execution failed" << std::endl;
            return 1;
        }
    } else {
        // Run example code
        std::cout << "No script provided. Running example..." << std::endl;
        std::cout << std::endl;
        
        std::string example_code = R"(
import aivy_api

# Log a message
aivy_api.Infrastructure.log("INFO", "Hello from Python guest!")

# Get data directory
data_dir = aivy_api.Infrastructure.get_data_directory()
print(f"Data directory from Python: {data_dir}")

# Save some data
aivy_api.Infrastructure.save_data("test.txt", "Hello from Python!")
print("Data saved successfully")

# Load the data back
data = aivy_api.Infrastructure.load_data("test.txt")
print(f"Loaded data: {data}")

print("\nExample completed successfully!")
)";

        if (!engine.executeCode(example_code)) {
            std::cerr << "Example execution failed" << std::endl;
            return 1;
        }
    }

    std::cout << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "    Aivy shutdown complete        " << std::endl;
    std::cout << "==================================" << std::endl;

    return 0;
}
