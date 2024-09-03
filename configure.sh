#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the build directory
BUILD_DIR=build/

# Remove the build directory if it exists
rm -rf $BUILD_DIR

# Create the build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Run CMake to configure the project
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B $BUILD_DIR
