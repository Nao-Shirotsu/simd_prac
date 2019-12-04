#pragma once

#include <random>

class RandomGenerator {
public:
  inline RandomGenerator() 
    : randEngine(std::random_device()())
    , distr(-100.0f, 100.0f) {}

  inline float operator()() {
    return distr(randEngine);
  }

private:
  std::default_random_engine randEngine;
  std::uniform_real_distribution<float> distr;
};