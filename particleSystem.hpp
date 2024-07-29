#pragma once

class ParticleSystem {
public:
  ParticleSystem();
  ~ParticleSystem();

  void onUpdate(const float &deltaTime);
  void onRender();
  void emit(const ParticleProp &prop);
  void nextPart();

private:
  std::vector<Particle> particlePool;
  size_t poolSize = 1000;
  unsigned int poolIndex;

  Shader partShader;
  unsigned int VAO = 0;
  unsigned int VBO = 0;
  unsigned int EBO = 0;

  unsigned int uniTransLoc = 0;
  unsigned int uniColorLoc = 0;
  unsigned int uniViewLoc = 0;
};
