#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glad/include/glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include <vector>

#include "particle.hpp"
#include "shaderLib/shader.h"

#include "particleSys.hpp"

const unsigned int WINDOW_HEIGHT = 800;
const unsigned int WINDOW_WIDTH = 800;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // Init GLFW
  if (!glfwInit()) {
    std::cout << "[ERROR] Couldn't load glfw\n";
    return -1;
  }

  // GLFW hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "App", 0, 0);
  if (!window) {
    std::cout << "[ERROR] Couldn't create glfw window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  // Set the viewport
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glEnable(GL_DEPTH_TEST);

  float deltaTime = 0;
  float lastFrame = 0;

  ParticleSystem ParticleSys;

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ParticleSys.onUpdate(deltaTime);
    ParticleSys.onRender();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
