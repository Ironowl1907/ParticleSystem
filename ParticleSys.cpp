#include "ParticleSys.h"
#include "glad/include/glad/glad.h"
#include "glm/glm/glm.hpp"
#include "particle.h"
#include "shaderLib/shader.h"
#include <iostream>

void ParticleSystem::Emit(ParticleProps props) {
  Particle &part = particlePool[poolIndex];

  part.active = true;

  part.position = props.InitialPos;
  part.Velocity = props.InitialVelocity;

  // Color
  part.colorBegin = props.InitialColor;
  part.colorEnd = props.FinalColor;

  // Size
  part.sizeBegin = props.sizeBeguin;
  part.sizeEnd = props.sizeEnd;

  poolIndex++;
  if (poolIndex >= poolSize)
    poolIndex = 0;
}

void ParticleSystem::OnRender() {

  if (VBO) {
    std::cout << "Genearting the buffers\n";
    float vertices[] = {
        -0.5f, 0.5f,  1.0f, //
        0.5f,  0.5f,  1.0f, //
        -0.5f, -0.5f, 1.0f, //
        0.5f,  -0.5f, 1.0f  //
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Binding Vertex Array Object (first thing)
    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(vertices), GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    Shader ParticleShader;
    ParticleShader.ParseFile("res/shaders/Particle.glsl");
    ParticleShader.CreateShader();
    glUseProgram(ParticleShader.ProgramID);

    unsigned int modelUniform =
        glGetUniformLocation(ParticleShader.ProgramID, "u_model");
    unsigned int viewUniform =
        glGetUniformLocation(ParticleShader.ProgramID, "u_view");
    unsigned int transformUniform =
        glGetUniformLocation(ParticleShader.ProgramID, "u_transform");

    defaultPartProp.InitialPos = {2, 2};

    defaultPartProp.sizeBeguin = 0.5f;
    defaultPartProp.sizeEnd = 0.1f;

    defaultPartProp.InitialColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    defaultPartProp.FinalColor = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

    defaultPartProp.InitialVelocity = glm::vec2(1.0f, 1.0f);
  }

  for (Particle &part : particlePool) {
    if (!part.active)
      continue;
    if (part.LifeRemaining < 0.0f) {
      part.active = false;
      continue;
    }
    // Render
    transform = glm::translate(glm::mat4(1.0f),
                               {part.position.x, part.position.y, 1.0f});
  }
}
