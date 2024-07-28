#ifndef PART_SYS
#define PART_SYS

class ParticleSystem {
public:
  ParticleSystem();
  ~ParticleSystem();

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
