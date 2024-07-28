struct Particle {
  glm::vec3 possition;
  glm::vec2 velocity;

  glm::vec4 InitColor;
  glm::vec4 FinalColor;

  unsigned int InitSize;
  unsigned int FinalSize;

  float totalLive;
  float remainingLive;

  bool active = false;
};

struct particleProp {
  glm::vec3 possition;
  glm::vec2 velocity;

  glm::vec4 InitColor;
  glm::vec4 FinalColor;

  float InitSize;
  float FinalSize;

  float totalLive = 1.0f;
};
