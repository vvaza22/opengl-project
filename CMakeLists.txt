cmake_minimum_required(VERSION 3.22.1)

# Set the project name
project(opengl-project VERSION 1.0)
set(PROJECT_NAME openglproject)

# Add the submodule
add_subdirectory(external/matrix-slayer)

# Include directories from the submodule
include_directories(${CMAKE_SOURCE_DIR}/external/matrix-slayer/include)

# Recursively find all .cpp files in the src directory
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add the library
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Specify the include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the C++ standard to C++17
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Set the most paranoid properties for g++
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wcast-align
        -Wconversion
        -Wsign-conversion
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
    )
endif()

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
    m
    glm
	matrixslayer
)

# Copy src/glsl to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/glsl $<TARGET_FILE_DIR:${PROJECT_NAME}>/glsl
)

# Copy data to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)