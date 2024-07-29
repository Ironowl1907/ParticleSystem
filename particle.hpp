#pragma once

struct Particle {
  glm::vec2 position, velocity;
  glm::vec4 ColorBegin, ColorEnd;
  float rotation;
  float sizeBegin, sizeEnd;
  float live, remainingLife = 1;
  bool alive = false;
};

struct ParticleProp {
  glm::vec2 position, velocity;
  glm::vec4 ColorBegin, ColorEnd;
  float rotation;
  float sizeBegin, sizeEnd;
  float live = 1;
};
