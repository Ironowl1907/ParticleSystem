#ifndef def_Particle
#define def_Particle
#include "glm/glm.hpp"

class Particle {
public:
  glm::vec2 position;
  glm::vec2 Velocity;
  glm::vec4 colorBegin, colorEnd;

  float sizeBegin, sizeEnd;
  float totalLife, LifeRemaining;

  bool active = false;

  void operator=(Particle &other) {
    position = other.position;
    Velocity = other.Velocity;
    colorBegin = other.colorBegin;
    colorEnd = other.colorEnd;
    sizeEnd = other.sizeEnd;
    sizeBegin = other.sizeBegin;
    totalLife = other.totalLife;
    LifeRemaining = other.LifeRemaining;
    active = other.active;
  }
};

#endif // Particle
