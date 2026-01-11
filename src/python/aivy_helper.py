"""
Aivy Helper Module for Python Guest Scripts

This module provides convenience functions and utilities
for Python guest scripts running in the Aivy platform.
"""

try:
    import aivy_api
except ImportError:
    print("Warning: aivy_api module not found. Make sure you're running within Aivy host.")
    aivy_api = None


class Logger:
    """Convenience wrapper for logging"""
    
    @staticmethod
    def info(message: str):
        """Log an info message"""
        if aivy_api:
            aivy_api.Infrastructure.log("INFO", message)
        else:
            print(f"[INFO] {message}")
    
    @staticmethod
    def warning(message: str):
        """Log a warning message"""
        if aivy_api:
            aivy_api.Infrastructure.log("WARNING", message)
        else:
            print(f"[WARNING] {message}")
    
    @staticmethod
    def error(message: str):
        """Log an error message"""
        if aivy_api:
            aivy_api.Infrastructure.log("ERROR", message)
        else:
            print(f"[ERROR] {message}")


class Storage:
    """Convenience wrapper for file storage"""
    
    @staticmethod
    def save(path: str, data: str) -> bool:
        """Save data to file"""
        if aivy_api:
            return aivy_api.Infrastructure.save_data(path, data)
        else:
            try:
                with open(path, 'w') as f:
                    f.write(data)
                return True
            except Exception as e:
                print(f"Error saving: {e}")
                return False
    
    @staticmethod
    def load(path: str) -> str:
        """Load data from file"""
        if aivy_api:
            return aivy_api.Infrastructure.load_data(path)
        else:
            try:
                with open(path, 'r') as f:
                    return f.read()
            except Exception as e:
                print(f"Error loading: {e}")
                return ""
    
    @staticmethod
    def list_files(directory: str = ".") -> list:
        """List files in directory"""
        if aivy_api:
            return aivy_api.Infrastructure.list_files(directory)
        else:
            import os
            return os.listdir(directory)
    
    @staticmethod
    def get_data_dir() -> str:
        """Get data directory path"""
        if aivy_api:
            return aivy_api.Infrastructure.get_data_directory()
        else:
            return "./data"


# Convenience instances
log = Logger()
storage = Storage()


__all__ = ['Logger', 'Storage', 'log', 'storage']
