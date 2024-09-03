# TODO: When changing .hpp files Makefile does not recompile objects. Can lead to confusion

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
INCLUDE_DIR = include
GLSL_DIR = $(SRC_DIR)/glsl

# Compiler
CXX = g++
# CXXFLAGS = -std=c++17 -Wall -Wconversion -Werror -g -I$(INCLUDE_DIR)
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wfloat-equal -Wpointer-arith -Wcast-qual -Wcast-align -Wformat=2 -Wnull-dereference -Wduplicated-cond -Wlogical-op -Wuseless-cast -Wdouble-promotion -Wstrict-overflow=5 -g -I$(INCLUDE_DIR)
LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm -lglm
# Linker flags only for testing
# main() for tests is included inside lgtest_main
TEST_LDFLAGS = -pthread -lgtest -lgtest_main

# Entry point for the application
MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Find every cpp file in the source directory
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

# Exclude main.cpp from sources
SRCS := $(filter-out $(MAIN_SRC), $(SRCS))

# We need to create object files for each cpp file in the build directory(except for main.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Find every test file
# Test files must end with _test.cpp
TEST_SRCS = $(shell find $(TEST_DIR) -name '*_test.cpp')

# Create objects for each test
# Actual source file will be compiled into myfile.o and test file into myfile_test.o in the same folder
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# List of .glsl files
GLSL_SRCS = $(shell find $(GLSL_DIR) -name '*.glsl')
GLSL_BUILD = $(GLSL_SRCS:$(SRC_DIR)/%.glsl=$(BUILD_DIR)/%.glsl)

# Executable file location
TARGET_FILE_NAME = main.out
TARGET = $(BUILD_DIR)/$(TARGET_FILE_NAME)

# Executable file that runs tests
TEST_RUNNER_TARGET = $(BUILD_DIR)/test_runner.out

# Build everything but don't run
all: $(TARGET) $(GLSL_BUILD)

# make run to build the application and run
run: $(TARGET) $(GLSL_BUILD)
	cd $(BUILD_DIR) && ./$(TARGET_FILE_NAME)

# Build the application and tests and then run the tests
test: $(TEST_RUNNER_TARGET)
	./$(TEST_RUNNER_TARGET)

# Delete build directory
clean:
	rm -rf $(BUILD_DIR)

########################### SOURCE ###########################

# Build the executable file
$(TARGET): $(MAIN_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
	rm -rf $(BUILD_DIR)/data
	cp -r data $(BUILD_DIR)/data

# Build object file for each cpp file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< $(LDFLAGS) -o $@

$(BUILD_DIR)/%.glsl: $(SRC_DIR)/%.glsl
	@mkdir -p $(dir $@)
	cp $< $@

########################### TESTS ###########################

# Build the test_runner (LDFLAGS ORDER MATTERS)
$(TEST_RUNNER_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ $(TEST_LDFLAGS) -o $@

# Build object files for tests
$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%_test.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< $(TEST_LDFLAGS) -o $@

# Tell make that these are labels and not actual files
.PHONY: all run test clean