#include "Vector3.hpp"

#include <immintrin.h>
#include <xmmintrin.h>

Vector3f::Vector3f() noexcept 
    : x(0)
    , y(0)
    , z(0) {}

Vector3f::Vector3f(const float x_, const float y_, const float z_) noexcept 
    : x(x_)
    , y(y_)
    , z(z_) {}

bool operator==(const Vector3f& lhs, const Vector3f& rhs) noexcept {
  return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

std::ostream& operator<<(std::ostream& ost, const Vector3f& vec) noexcept {
  return ost << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

float Dot3D(const Vector3f& lhs, const Vector3f& rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float Dot3DSimd(const Vector3f& lhs, const Vector3f& rhs) noexcept {
  __m128 left = _mm_set_ps(0.0f, lhs.x, lhs.y, lhs.z);
  __m128 right = _mm_set_ps(0.0f, rhs.x, rhs.y, rhs.z);
  __m128 resultReg = _mm_mul_ps(left, right);
  alignas(16) float resultMem[4];
  _mm_store_ps(reinterpret_cast<float*>(resultMem), resultReg);
  return resultMem[0] + resultMem[1] + resultMem[2];
}

Vector3f Cross3D(const Vector3f& lhs, const Vector3f& rhs) noexcept {
  return Vector3f(lhs.y * rhs.z - lhs.z * rhs.y,
                  lhs.z * rhs.x - lhs.x * rhs.z,
                  lhs.x * rhs.y - lhs.y * rhs.x);
}

Vector3f Cross3DSimd(const Vector3f& lhs, const Vector3f& rhs) noexcept {
  __m256 left = _mm256_set_ps(0.0f, 0.0f, lhs.y, lhs.z, lhs.x, lhs.z, lhs.x, lhs.y);
  __m256 right = _mm256_set_ps(0.0f, 0.0f, rhs.z, rhs.x, rhs.y, rhs.y, rhs.z, rhs.x);
  __m256 resultReg = _mm256_mul_ps(left, right);
  alignas(32) float resultMem[16];
  _mm256_store_ps(reinterpret_cast<float*>(resultMem), resultReg);
  return Vector3f(resultMem[5] - resultMem[2], resultMem[4] - resultMem[1], resultMem[3] - resultMem[0]);
}
