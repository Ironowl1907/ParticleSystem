#include "glad/include/glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include "shaderLib/shader.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "particle.hpp"
#include "particleSystem.hpp"

const unsigned int WINDOW_HEIGHT = 800;
const unsigned int WINDOW_WIDTH = 800;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

int main() {
  // Init GLFW
  if (!glfwInit()) {
    std::cout << "[ERROR] Couldn't load glfw\n";
    return -1;
  }

  // GLFW hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_BLEND);
  glDebugMessageCallback(MessageCallback, 0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Set the viewport
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  ParticleProp defaultPart;
  defaultPart.position = {0.5f, 0.5f};
  defaultPart.velocity = {0.02f, 0.04};
  defaultPart.ColorBegin = {1.0f, 0.0f, 0.0f, 1.0f};
  defaultPart.ColorEnd = {1.0f, 1.0f, 1.0f, 0.0f};
  defaultPart.rotation = 50.0f;
  defaultPart.sizeBegin = 1.0f;
  defaultPart.sizeEnd = 0.8f;

  defaultPart.live = 10.0f;

  ParticleProp defaultPart2;
  defaultPart2.position = {0.5f, 0.5f};
  defaultPart2.velocity = {-0.02f, -0.04};
  defaultPart2.ColorBegin = {1.0f, 0.0f, 0.0f, 1.0f};
  defaultPart2.ColorEnd = {1.0f, 1.0f, 1.0f, 0.0f};
  defaultPart2.rotation = 50.0f;
  defaultPart2.sizeBegin = 1.0f;
  defaultPart2.sizeEnd = 0.8f;

  defaultPart2.live = 10.0f;

  ParticleSystem partSys;
  partSys.emit(defaultPart);
  partSys.emit(defaultPart2);

  // Camera
  glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec3 target_pos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 view =
      glm::lookAt(camera_pos, target_pos, glm::vec3(0.0f, 1.0f, 0.0f));
  view = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f) * view;

  float deltaTime = 0;
  float lastFrame = 0;

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Render
    partSys.onUpdate(deltaTime);
    partSys.onRender(view);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
