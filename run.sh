#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the build directory
BUILD_DIR=build/

# Update glsl dir
rm -rf $BUILD_DIR/glsl
cp -r src/glsl $BUILD_DIR

# Change to the build directory and build the project
cd $BUILD_DIR && ./openglproject
