#include "glad/include/glad/glad.h"

#include "glm/glm.hpp"
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shaderLib/shader.h"

#include "particleSys.hpp"

glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float f) { return a + f * (b - a); }
glm::vec4 lerp(glm::vec4 a, glm::vec4 b, float f) { return a + f * (b - a); }
float lerp(float a, float b, float f) { return a + f * (b - a); }

ParticleSystem::ParticleSystem() {
  particlePool.reserve(particlePoolSize);
  poolPos = 0;
}

void ParticleSystem::nextPart() {
  ++poolPos;
  if (poolPos >= particlePoolSize)
    poolPos = 0;
}

void ParticleSystem::Emit(const particleProp &prop) {
  while (particlePool[poolPos].active)
    nextPart();
  Particle &part = particlePool[poolPos];

  part.possition = prop.possition;

  part.velocity = prop.velocity;

  part.InitColor = prop.InitColor;
  part.FinalColor = prop.FinalColor;

  part.InitSize = prop.InitSize;
  part.FinalSize = prop.FinalSize;

  part.active = true;
}

void ParticleSystem::onUpdate(const float &timeDelta) {
  for (Particle &part : particlePool) {

    if (!part.active)
      continue;

    if (part.remainingLive > 0) {
      part.active = false;
      continue;
    }
    part.remainingLive -= timeDelta;
  }
}
void ParticleSystem::onRender() {
  if (!VAO) {
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
                        0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f};

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    partShader.ParseFile("res/shaders/particleShader.glsl");
    partShader.CreateShader();
    uniModelPointer = glGetUniformLocation(partShader.ProgramID, "u_model");
    uniTransformPointer =
        glGetUniformLocation(partShader.ProgramID, "u_transform");
    uniColorPointer = glGetUniformLocation(partShader.ProgramID, "u_color");
  }
  for (Particle &part : particlePool) {
    if (!part.active)
      continue;

    float life = part.remainingLive / part.totalLive;

    glm::vec4 color = lerp(part.InitColor, part.FinalColor, life);
    float size = lerp(part.InitSize, part.FinalSize, life);

    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f),
                       {part.possition.x, part.possition.y, 1.0f}) *
        glm::scale(glm::mat4(1.0f), glm::vec3(size, size, 1.0f));

    glUniformMatrix4fv(uniTransformPointer, 1, GL_FALSE,
                       glm::value_ptr(transform));
    glUniform4f(uniColorPointer, color.r, color.g, color.b, color.a);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  }
}
