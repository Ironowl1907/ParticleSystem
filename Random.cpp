#include "Random.hpp"

Random::Random() : mt(std::random_device{}()), dist(0.0, 1.0) {}

float Random::Float() { return dist(mt); }
