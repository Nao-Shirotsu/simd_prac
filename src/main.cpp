#include "matrix4x4.hpp"
#include "randomgenerator.hpp"
#include "stopwatch.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <class ReturnTy, class LhsTy, class RhsTy>
void Benchmark(const std::vector<LhsTy>& lhs, const std::vector<RhsTy>& rhs, const size_t numCalc, std::function<ReturnTy(const LhsTy&, const RhsTy&)> Func, const char* const benchName) {
  // ���ʂ̃X�g�b�v�E�H�b�`(���g�͂�����std::chrono�֘A�֐��Ăяo��)
  StopWatch stopwatch;
  stopwatch.Start();
  for (auto i = 0u; i < numCalc; ++i) {
    Func(lhs[i], rhs[i]);
  }
  stopwatch.Stop();
  std::cout << benchName << " : " << stopwatch.GetMicroseconds() << " microsec" << std::endl;
  stopwatch.Reset();
}

int main(int argc, char* argv[]) {
  // �x���`�}�[�N�ł̉��Z��
  const auto numCalc = (argc > 1) ? std::stoul(argv[1]) : 100000;
  std::cout << "<<" << numCalc << " times calculations as Benchmark>>" << std::endl;

  // [-100.0, 100.0]�͈̔͂̈�l���z�ɏ�����^������������
  RandomGenerator rand;

  // ���Ԍv�� : 3�����x�N�g���̓��ρE�O��
  {
    std::vector<Vector3f> vecA(numCalc);
    std::vector<Vector3f> vecB(numCalc);
    for (auto i = 0u; i < numCalc; ++i) {
      vecA[i] = { rand(),
                  rand(),
                  rand() };
    }
    Benchmark<float, Vector3f, Vector3f>(vecA, vecB, numCalc, Dot3D, "normal Vector3 Dot");
    Benchmark<float, Vector3f, Vector3f>(vecA, vecB, numCalc, Dot3DSimd, "SIMD Vector3 Dot");
    Benchmark<Vector3f, Vector3f, Vector3f>(vecA, vecB, numCalc, Cross3D, "normal Vector3 Cross");
    Benchmark<Vector3f, Vector3f, Vector3f>(vecA, vecB, numCalc, Cross3DSimd, "SIMD Vector3 Cross");
  }

  // ���Ԍv�� : 4�����x�N�g���̓���
  {
    std::vector<Vector4f> vecA(numCalc);
    std::vector<Vector4f> vecB(numCalc);
    for (auto i = 0u; i < numCalc; ++i) {
      vecA[i] = { rand(),
                  rand(),
                  rand(),
                  rand() };
    }
    Benchmark<float, Vector4f, Vector4f>(vecA, vecB, numCalc, Dot4D, "normal Vector4 Dot");
    Benchmark<float, Vector4f, Vector4f>(vecA, vecB, numCalc, Dot4DSimd, "SIMD Vector4 Dot");
  }

  // ���Ԍv�� : 3�����x�N�g����4�����s��̐�
  {
    std::vector<Vector3f> vec(numCalc);
    std::vector<Matrix4x4> matrices(numCalc);
    for (auto i = 0u; i < numCalc; ++i) {
      vec[i] = { rand(),
                 rand(),
                 rand() };
      matrices[i] = { { rand(), rand(), rand(), rand() },
                      { rand(), rand(), rand(), rand() },
                      { rand(), rand(), rand(), rand() },
                      { rand(), rand(), rand(), rand() } };
    }
    Benchmark<Vector3f, Vector3f, Matrix4x4>(vec, matrices, numCalc, Multiply, "normal Vector*Matrix");
    Benchmark<Vector3f, Vector3f, Matrix4x4>(vec, matrices, numCalc, MultiplySimd, "SIMD Vector*Matrix");
  }
}