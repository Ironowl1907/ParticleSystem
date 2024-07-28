
struct Particle {
  glm::vec2 position, velocity;
  glm::vec4 ColorBegin, ColorEnd;
  glm::mat4 rotation;
  float sizeBegin, sizeEnd;
  float live, remainingLife;
  bool alive = false;
};

struct ParticleProp {
  glm::vec2 position, velocity;
  glm::vec4 ColorBegin, ColorEnd;
  glm::mat4 rotation;
  float sizeBegin, sizeEnd;
  float live;
};
