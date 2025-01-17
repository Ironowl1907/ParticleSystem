#include "glad/include/glad/glad.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtx/compatibility.hpp>

#include "particle.hpp"
#include "shaderLib/shader.h"

#include "particleSystem.hpp"

ParticleSystem::ParticleSystem() {
  particlePool.resize(poolSize);
  poolIndex = 0;
}
ParticleSystem::~ParticleSystem() {
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
}
void ParticleSystem::nextPart() {
  poolIndex = (poolIndex < poolSize) ? poolIndex + 1 : 0;
}

void ParticleSystem::onUpdate(const float &deltatime) {
  for (Particle &part : particlePool) {
    if (!part.alive)
      continue;
    /*std::cout << "Particle " << &part - &particlePool[0] << ": Velocity= ("*/
    /*          << part.velocity << "), Position = " << part.position.x << ' '*/
    /*          << part.position.y << '\n';*/
    if (part.remainingLife < 0) {
      part.alive = false;
      continue;
    }
    part.remainingLife -= deltatime;
    part.velocity = part.velocity * (1 - part.friction * deltatime);

    part.position = part.position + part.direction * part.velocity * deltatime;
    /*std::cout << "direction: ( " << part.direction.x << ' ' <<
     * part.direction.y*/
    /*          << ") velocity: (" << part.velocity << ")\n";*/
  }
}
void ParticleSystem::onRender(const glm::mat4 &cameraView) {
  if (!VAO) {
    std::cout << "Creating buffers" << '\n';

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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleCoords), particleCoords,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexElements),
                 vertexElements, GL_STATIC_DRAW);

    // Shader
    partShader.ParseFile("../res/shaders/particleShader.glsl");
    partShader.CreateShader();
    glUseProgram(partShader.ProgramID);

    // Uniforms
    uniTransLoc = glGetUniformLocation(partShader.ProgramID, "u_Transform");
    uniColorLoc = glGetUniformLocation(partShader.ProgramID, "u_Color");
    uniViewLoc = glGetUniformLocation(partShader.ProgramID, "u_View");
  }

  for (Particle &part : particlePool) {
    if (!part.alive)
      continue;

    float life = part.remainingLife / part.live;
    // Color
    glm::vec4 color = glm::lerp(part.ColorEnd, part.ColorBegin, life);

    // Transform
    float scale = glm::lerp(part.sizeEnd, part.sizeBegin, life);
    glm::mat4 scaleMat =
        glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f));

    glm::mat4 translate = glm::translate(
        glm::mat4(1.0f), glm::vec3(part.position.x, part.position.y, 0.0f));

    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(part.rotation),
                                   glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 transform = translate * rotate * scaleMat;
    glUniformMatrix4fv(uniTransLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform4f(uniColorLoc, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(uniViewLoc, 1, GL_FALSE, glm::value_ptr(cameraView));

    glBindVertexArray(VAO);
    glUseProgram(partShader.ProgramID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

void ParticleSystem::emit(const ParticleProp &prop) {

  Particle &part = particlePool[poolIndex];

  part.position = prop.position;
  part.direction = prop.direction;
  part.velocity = prop.velocity;
  part.friction = prop.friction;

  part.ColorBegin = prop.ColorBegin;
  part.ColorEnd = prop.ColorEnd;

  part.sizeBegin = prop.sizeBegin;
  part.sizeEnd = prop.sizeEnd;

  part.rotation = prop.rotation;

  part.live = prop.live;
  part.remainingLife = prop.live;

  part.alive = true;

  nextPart();
}
