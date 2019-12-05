#include "randomgenerator.hpp"
#include "stopwatch.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  // 普通のストップウォッチ(中身はただのstd::chrono関連関数呼び出し)
  StopWatch stopwatch;

  // 演算対象となる3次元ベクトルたちを確保
  const auto vecSize = (argc > 1) ? std::stoul(argv[1]) : 100000;
  std::vector<Vector3f> vec3A(vecSize);
  std::vector<Vector3f> vec3B(vecSize);
  RandomGenerator rand;
  for (auto i = 0u; i < vecSize; ++i) {
    vec3A[i] = { rand(), rand(), rand() };
    vec3B[i] = { rand(), rand(), rand() };
  }

  //~~~~~~~~~~~~~~~ここから3次元ベクトル内積・外積~~~~~~~~~~~~~~~
  // 時間計測 : 普通の3Dベクトル内積計算
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Dot(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SISD Vec3 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // 時間計測 : SIMD化3Dベクトル内積計算
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    DotSimd(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD Vec3 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // 時間計測 : 普通の3Dベクトル外積計算
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Cross(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SISD Vec3 Cross : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // 時間計測 : SIMD化3Dベクトル外積計算
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    CrossSimd(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD Vec3 Cross : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();


  // 演算対象となる4次元ベクトルたちを確保
  std::vector<Vector4f> vec4A(vecSize);
  std::vector<Vector4f> vec4B(vecSize);
  for (auto i = 0u; i < vecSize; ++i) {
    vec4A[i] = { rand(), rand(), rand(), rand() };
    vec4B[i] = { rand(), rand(), rand(), rand() };
  }

  //~~~~~~~~~~~~~~~ここから4次元ベクトル内積~~~~~~~~~~~~~~~
  // 時間計測 : 普通の4Dベクトル内積計算
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Dot(vec4A[i], vec4B[i]);
  }
  stopwatch.Stop();
  std::cout << "SISD Vec4 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // 時間計測 : SIMD化4Dベクトル内積計算
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    DotSimd(vec4A[i], vec4B[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD Vec4 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();
}