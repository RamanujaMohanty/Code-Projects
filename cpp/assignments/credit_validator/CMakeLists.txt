# Specifies the minimum version of CMake required to build the project.
# This ensures that the script is compatible with the user's CMake installation.
cmake_minimum_required(VERSION 3.10)

# Declares the project name and the programming language used.
# This sets up the project and enables C++ compilation.
project(MyProject CXX)

# Sets the C++ standard to be used for compiling the code.
# C++17 is a modern standard with many useful features.
# The "REQUIRED" keyword ensures that the compiler supports this standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adds an executable target to the build.
# This command tells CMake to create an executable named "my_executable"
# from the specified source files.
add_executable(credit_validator credit_validator.cpp)

# (Optional) Adds include directories.
# This is useful if your project has header files in different directories.
# target_include_directories(my_executable PRIVATE include)

# (Optional) Links libraries to the executable.
# This is necessary if your code uses external libraries.
# For example, to link the pthreads library:
# target_link_libraries(my_executable PRIVATE pthread)