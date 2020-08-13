
#pragma once

#include <random>

class NiceRand {
private:
  std::mt19937 gen;

public:
  NiceRand(unsigned int _seed)
    : gen(_seed){};
  ~NiceRand(){};

  NiceRand(const NiceRand&) = delete;
  NiceRand(NiceRand&&) = delete;

  NiceRand& operator=(const NiceRand&) = delete;
  NiceRand& operator=(NiceRand&&) = delete;

public:
  template<typename type>
  type GetRealUniform(type min, type max) {
    return std::uniform_real_distribution<type>(min, max)(gen);
  }

  template<typename type>
  type GetRealNormal(type mean, type deviation) {
    return std::normal_distribution<type>(mean, deviation)(gen);
  }
};