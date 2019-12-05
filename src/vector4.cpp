#include "vector4.hpp"

#include <immintrin.h>
#include <xmmintrin.h>

Vector4f::Vector4f()
    : x(0)
    , y(0)
    , z(0)
    , w(0) {}

Vector4f::Vector4f(const float x_, const float y_, const float z_, const float w_)
    : x(x_)
    , y(y_)
    , z(z_)
    , w(w_) {}

bool operator==(const Vector4f& lhs, const Vector4f& rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
}

std::ostream& operator<<(std::ostream& ost, const Vector4f& vec) {
  return ost << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}

float Dot(const Vector4f& lhs, const Vector4f& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

float DotSimd(const Vector4f& lhs, const Vector4f& rhs) {
  __m128 left = _mm_load_ps(reinterpret_cast<const float*>(lhs.vec));
  __m128 right = _mm_load_ps(reinterpret_cast<const float*>(rhs.vec));
  __m128 resultReg = _mm_mul_ps(left, right);
  alignas(16) float resultMem[4];
  _mm_store_ps(reinterpret_cast<float*>(resultMem), resultReg);
  return resultMem[0] + resultMem[1] + resultMem[2] + resultMem[3];
}
