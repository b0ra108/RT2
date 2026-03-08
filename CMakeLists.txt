cmake_minimum_required(VERSION 3.20)

project(RayTracer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RayTracer
    src/main.cpp
    src/raytracer.cpp
)

target_include_directories(RayTracer PRIVATE include)
