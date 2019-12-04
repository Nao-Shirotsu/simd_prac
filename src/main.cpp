#include "stopwatch.hpp"
#include "vector3.hpp"
#include "randomgenerator.hpp"

#include <iostream>
#include <vector>

int main() {
  constexpr auto vecSize = 100000;
  std::vector<Vector3f> vectorsA(vecSize);
  std::vector<Vector3f> vectorsB(vecSize);
  RandomGenerator rand;
  for (auto i = 0u; i < vecSize; ++i) {
    vectorsA[i] = { rand(), rand(), rand() };
    vectorsB[i] = { rand(), rand(), rand() };
  }
  
  StopWatch stopwatch;
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Dot(vectorsA[i], vectorsB[i]);
  }
  stopwatch.Stop();
  std::cout << "Normal Dot : " << stopwatch.GetMilliseconds() << std::endl;
  stopwatch.Reset();

  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    DotSimd(vectorsA[i], vectorsB[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD   Dot : " << stopwatch.GetMilliseconds() << std::endl;
  stopwatch.Reset();

  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Cross(vectorsA[i], vectorsB[i]);
  }
  stopwatch.Stop();
  std::cout << "Normal Cross : " << stopwatch.GetMilliseconds() << std::endl;
  stopwatch.Reset();

  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    CrossSimd(vectorsA[i], vectorsB[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD   Cross : " << stopwatch.GetMilliseconds() << std::endl;
  stopwatch.Reset();
}