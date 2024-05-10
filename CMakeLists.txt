cmake_minimum_required(VERSION 3.10)

# Set the project name
project(seed)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(${PROJECT_NAME} source/main.cpp)