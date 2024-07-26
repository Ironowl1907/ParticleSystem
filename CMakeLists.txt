cmake_minimum_required(VERSION 3.29)

project(Particles)
add_executable(${PROJECT_NAME} main.cpp)

add_library(glad STATIC glad/src/glad.c)
target_link_libraries(${PROJECT_NAME} glad)


add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
