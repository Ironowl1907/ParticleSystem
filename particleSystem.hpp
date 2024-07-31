#pragma once

class ParticleSystem {
public:
  ParticleSystem();
  ~ParticleSystem();

  void onUpdate(const float &deltaTime);
  void onRender(const glm::mat4 &cameraView);
  void emit(const ParticleProp &prop);
  void nextPart();

private:
  static unsigned int WINDOW_HEIGHT2, WINDOW_WIDTH2;
  std::vector<Particle> particlePool;
  size_t poolSize = 10000;
  unsigned int poolIndex;

  Shader partShader;
  unsigned int VAO = 0;
  unsigned int VBO = 0;
  unsigned int EBO = 0;

  unsigned int uniTransLoc = 0;
  unsigned int uniColorLoc = 0;
  unsigned int uniViewLoc = 0;
  unsigned int uniProjectionLoc = 0;
};
