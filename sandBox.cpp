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

ParticleSystem partSys;
ParticleProp defaultParticle;
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
  float ndc_x = xpos / 800.0 * 2.0 - 1.0;
  float ndc_y = 1.0 - ypos / 800.0 * 2.0;
  defaultParticle.position.x = ndc_x;
  defaultParticle.position.y = ndc_y;
  partSys.emit(defaultParticle);
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
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Set the viewport
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  defaultParticle.position = {0.5f, 0.5f};
  defaultParticle.velocity = {-0.02f, -0.04};
  defaultParticle.ColorBegin = {1.0f, 0.0f, 0.0f, 1.0f};
  defaultParticle.ColorEnd = {1.0f, 1.0f, 1.0f, 0.0f};
  defaultParticle.rotation = 50.0f;
  defaultParticle.sizeBegin = 0.2f;
  defaultParticle.sizeEnd = 0.1f;

  defaultParticle.live = 1.0f;

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
