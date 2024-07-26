#include "ParticleSys.h"
#include "glad/include/glad/glad.h"
#include "particle.h"

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
  if (poolIndex > poolSize - 1)
    poolIndex = 0;
}

void ParticleSystem::OnRender() {

  if (VBO) {

    float vertices[] =
        {
            -0.5f,
        }

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Binding Vertex Array Object (first thing)
    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  }
}
