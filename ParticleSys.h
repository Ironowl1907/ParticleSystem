#include "glm/glm.hpp"
#include "particle.h"
#include <cstddef>
#include <vector>

struct ParticleProps {
  glm::vec2 InitialPos, InitialVelocity;
  glm::vec4 InitialColor, FinalColor;
  float LifeTime = 1;
};

class ParticleSystem {
  ParticleSystem();
  ~ParticleSystem();
  void Emit(ParticleProps props);
  void OnUpdate(unsigned int timeSec);
  void OnRender();
  size_t ParticleBuffer = 1000;
  std::vector<Particle> particlePool;
};
