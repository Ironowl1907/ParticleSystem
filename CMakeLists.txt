cmake_minimum_required(VERSION 3.29)

# Project name and version
project(Particles VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable and source files
add_executable(${PROJECT_NAME} main.cpp ParticleSys.cpp)

# Add the glad library
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# Link glad to the project
target_link_libraries(${PROJECT_NAME} glad)

# Add the ShadersLib library
add_library(Shader STATIC shaderLib/main.cpp) 
target_include_directories(glad PUBLIC shaderLib/shader.h)

# Link glad to the project
target_link_libraries(${PROJECT_NAME} glad)

# Add GLFW subdirectory and link it
add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
