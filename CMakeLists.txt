cmake_minimum_required(VERSION 3.10)

project(YispInterpreter)

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Add all source files
file(GLOB SOURCES "src/*.cpp")

# Create an executable target
add_executable(yisprun ${SOURCES})