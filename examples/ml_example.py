"""
Example Python Guest Script for Aivy

This script demonstrates how Python guest scripts can use
the C++ host infrastructure API to perform ML tasks.
"""

import aivy_api


def train_model(data_path: str):
    """
    Example ML training function
    
    In a real scenario, this would:
    - Load training data using Infrastructure.load_data()
    - Train a model
    - Save the model using Infrastructure.save_data()
    """
    aivy_api.Infrastructure.log("INFO", "Starting model training...")
    
    # Simulate training
    aivy_api.Infrastructure.log("INFO", "Training in progress...")
    
    # Save model
    model_data = "trained_model_weights"
    success = aivy_api.Infrastructure.save_data("models/my_model.pkl", model_data)
    
    if success:
        aivy_api.Infrastructure.log("INFO", "Model saved successfully!")
    else:
        aivy_api.Infrastructure.log("ERROR", "Failed to save model")
    
    return success


def inference(model_path: str, input_data: str):
    """
    Example ML inference function
    """
    aivy_api.Infrastructure.log("INFO", "Starting inference...")
    
    # Load model
    model = aivy_api.Infrastructure.load_data(model_path)
    
    if not model:
        aivy_api.Infrastructure.log("ERROR", f"Failed to load model: {model_path}")
        return None
    
    aivy_api.Infrastructure.log("INFO", f"Model loaded: {len(model)} bytes")
    
    # Simulate inference
    result = f"prediction_for_{input_data}"
    
    aivy_api.Infrastructure.log("INFO", f"Inference result: {result}")
    return result


def main():
    """
    Main entry point for the guest script
    """
    aivy_api.Infrastructure.log("INFO", "=== Python Guest Script Started ===")
    
    # Get data directory
    data_dir = aivy_api.Infrastructure.get_data_directory()
    print(f"Working in data directory: {data_dir}")
    
    # Train a model
    train_model("training_data.csv")
    
    # Run inference
    result = inference("models/my_model.pkl", "test_input")
    
    # List files in models directory
    try:
        files = aivy_api.Infrastructure.list_files("models")
        print(f"Files in models directory: {files}")
    except Exception as e:
        print(f"Error listing files: {e}")
    
    aivy_api.Infrastructure.log("INFO", "=== Python Guest Script Completed ===")


if __name__ == "__main__":
    main()
