#pragma once

#include <random>

class Random {
public:
  Random();
  float Float();

private:
  std::mt19937 mt;
  std::uniform_real_distribution<double> dist;
};
