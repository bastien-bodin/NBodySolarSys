cmake_minimum_required(VERSION 3.10)
project(NBodySimulator VERSION 1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the headers directory
include_directories(include)

# Define the executable and the source files needed
add_executable(nbody_sim
    main.cpp
    src/Vector3D.cpp
    src/CelestialBody.cpp
)