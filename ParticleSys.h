#ifndef CLASS_PARTICLESYSTEM
#define CLASS_PARTICLESYSTEM

#ifndef GLM
#define GLM
#include "glm/glm.hpp"
#endif

#include "particle.h"
class ParticleSystem {
  ParticleSystem();
  ~ParticleSystem();

public:
  struct ParticleProps {
    glm::vec2 InitialPos, InitialVelocity;
    glm::vec4 InitialColor, FinalColor;
    float sizeBeguin, sizeEnd;
    float LifeTime = 1;
  };
  void Emit(ParticleProps props);
  void OnUpdate(unsigned int timeSec);
  void OnRender();
  unsigned int poolIndex = 0;
  size_t poolSize = 1000;
  std::vector<Particle> particlePool;
  unsigned int VBO = 0, VAO = 0, EBO = 0;
  ParticleProps defaultPartProp;

  // Color
  glm::vec4 color;
  // Rotatations and scaling
  glm::vec3 model;
  // Movements
  glm::vec3 transform;
  // Camera
  glm::vec3 projection;
};
#endif // CLASS_PARTICLESYSTEM
