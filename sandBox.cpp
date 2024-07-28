#include "glad/include/glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>

#include "particle.hpp"
#include "shaderLib/shader.h"

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

  // Set the viewport
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glEnable(GL_DEPTH_TEST);

  ParticleProp defaultPart;
  defaultPart.position = {0.0f, 0.0f};
  defaultPart.velocity = {0.2f, 0.4};
  defaultPart.ColorBegin = {1.0f, 0.0f, 0.0f, 1.0f};
  defaultPart.ColorEnd = {0.0f, 0.0f, 1.0f, 1.0f};
  defaultPart.rotation = glm::mat4(1.0f);
  defaultPart.sizeBegin = 1.0f;
  defaultPart.sizeEnd = 0.1f;

  float particleCoords[] = {
      -0.5f, 0.5f,  0.0f, // top left
      0.5f,  0.5f,  0.0f, // top right
      -0.5f, -0.5f, 0.0f, // bottom left
      0.5f,  -0.5f, 0.0f  // bottom right
  };

  unsigned int vertexElements[] = {
      0, 1, 2, //
      2, 1, 3  //
  };

  unsigned int VAO, VBO, EBO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(particleCoords), particleCoords,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexElements), vertexElements,
               GL_STATIC_DRAW);

  // Shader
  Shader partShader;
  partShader.ParseFile("../res/shaders/particleShader.glsl");
  partShader.CreateShader();
  glUseProgram(partShader.ProgramID);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
