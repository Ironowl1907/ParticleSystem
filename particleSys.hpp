#ifndef PART_SYS
#define PART_SYS

struct Particle {
  glm::vec3 possition;
  glm::vec2 velocity;

  glm::vec4 InitColor;
  glm::vec4 FinalColor;

  unsigned int InitSize;
  unsigned int FinalSize;

  float totalLive = 1.0f;
  float remainingLive;

  bool active = false;
};

class ParticleSystem {
  ParticleSystem();
  ~ParticleSystem();

  struct particleProp {
    glm::vec3 possition;
    glm::vec2 velocity;

    glm::vec4 InitColor;
    glm::vec4 FinalColor;

    float InitSize;
    float FinalSize;

    float totalLive;
  };

  void Emit(const particleProp &prop);
  void onUpdate(const float &timeDelta);
  void onRender();
  void nextPart();

  std::vector<Particle> particlePool;
  const size_t particlePoolSize = 1000;
  unsigned int poolPos;

  unsigned int VAO = 0;

  Shader partShader;
  unsigned int uniTransformPointer;
  unsigned int uniModelPointer;
  unsigned int uniColorPointer;
};

#endif // PART_SYS
