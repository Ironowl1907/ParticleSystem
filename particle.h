#ifndef def_Particle
#define def_Particle
#include "glm/glm.hpp"

class Particle {
  glm::vec2 position;
  glm::vec2 Velocity;
  glm::vec4 colorBegin, colorEnd;

  float sizeBegin, sizeEnd;
  float LifeRemaining;

  bool active = false;
};

#endif // Particle
