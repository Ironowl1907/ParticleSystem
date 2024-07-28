cmake_minimum_required(VERSION 3.29)

project(App)
add_executable(${PROJECT_NAME} sandBox.cpp)

add_library(glad STATIC glad/src/glad.c)
target_link_libraries(${PROJECT_NAME} glad)

add_library(ShaderLib STATIC shaderLib/main.cpp)
target_link_libraries(${PROJECT_NAME} ShaderLib)

add_subdirectory(glfw)
target_link_libraries(App glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(App OpenGL::GL)
