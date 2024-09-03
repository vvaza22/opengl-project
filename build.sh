#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the build directory
BUILD_DIR=build/

# Change to the build directory and build the project
cd $BUILD_DIR && make
