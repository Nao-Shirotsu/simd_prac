#include "randomgenerator.hpp"
#include "stopwatch.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  // ���ʂ̃X�g�b�v�E�H�b�`(���g�͂�����std::chrono�֘A�֐��Ăяo��)
  StopWatch stopwatch;

  // ���Z�ΏۂƂȂ�3�����x�N�g���������m��
  const auto vecSize = (argc > 1) ? std::stoul(argv[1]) : 100000;
  std::vector<Vector3f> vec3A(vecSize);
  std::vector<Vector3f> vec3B(vecSize);
  RandomGenerator rand;
  for (auto i = 0u; i < vecSize; ++i) {
    vec3A[i] = { rand(), rand(), rand() };
    vec3B[i] = { rand(), rand(), rand() };
  }

  //~~~~~~~~~~~~~~~��������3�����x�N�g�����ρE�O��~~~~~~~~~~~~~~~
  // ���Ԍv�� : ���ʂ�3D�x�N�g�����όv�Z
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Dot(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SISD Vec3 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // ���Ԍv�� : SIMD��3D�x�N�g�����όv�Z
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    DotSimd(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD Vec3 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // ���Ԍv�� : ���ʂ�3D�x�N�g���O�όv�Z
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Cross(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SISD Vec3 Cross : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // ���Ԍv�� : SIMD��3D�x�N�g���O�όv�Z
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    CrossSimd(vec3A[i], vec3B[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD Vec3 Cross : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();


  // ���Z�ΏۂƂȂ�4�����x�N�g���������m��
  std::vector<Vector4f> vec4A(vecSize);
  std::vector<Vector4f> vec4B(vecSize);
  for (auto i = 0u; i < vecSize; ++i) {
    vec4A[i] = { rand(), rand(), rand(), rand() };
    vec4B[i] = { rand(), rand(), rand(), rand() };
  }

  //~~~~~~~~~~~~~~~��������4�����x�N�g������~~~~~~~~~~~~~~~
  // ���Ԍv�� : ���ʂ�4D�x�N�g�����όv�Z
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    Dot(vec4A[i], vec4B[i]);
  }
  stopwatch.Stop();
  std::cout << "SISD Vec4 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();

  // ���Ԍv�� : SIMD��4D�x�N�g�����όv�Z
  stopwatch.Start();
  for (auto i = 0u; i < vecSize; ++i) {
    DotSimd(vec4A[i], vec4B[i]);
  }
  stopwatch.Stop();
  std::cout << "SIMD Vec4 Dot : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();
}