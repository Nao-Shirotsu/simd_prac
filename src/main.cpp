#include "stopwatch.hpp"
#include "vector3.hpp"
#include "randomgenerator.hpp"

#include <iostream>
#include <vector>

int main() {
  /*util::StopWatch timer;
  timer.Start();
  timer.Stop();
  std::cout << timer.GetMilliseconds() << std::endl;*/

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

  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    DotSimd(vectorsA[i], vectorsB[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD   Dot : " << stopwatch.GetMilliseconds() << std::endl;
}