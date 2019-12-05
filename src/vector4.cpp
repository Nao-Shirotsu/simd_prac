#include "vector4.hpp"
#include "randomgenerator.hpp"

#include <immintrin.h>
#include <xmmintrin.h>

Vector4f::Vector4f() noexcept 
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
    , w(0.0f) {}

Vector4f::Vector4f(const float x_, const float y_, const float z_, const float w_) noexcept 
    : x(x_)
    , y(y_)
    , z(z_)
    , w(w_) {}

const float& Vector4f::operator[](const size_t idx) const noexcept {
  return vec[idx];
}

//Vector4f::operator Vector3f() const noexcept {
//  return Vector3f(x, y, z);
//}

bool operator==(const Vector4f& lhs, const Vector4f& rhs) noexcept {
  return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
}

std::ostream& operator<<(std::ostream& ost, const Vector4f& vec) noexcept {
  return ost << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}

float Dot4D(const Vector4f& lhs, const Vector4f& rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

float Dot4DSimd(const Vector4f& lhs, const Vector4f& rhs) noexcept {
  __m128 left = _mm_load_ps(reinterpret_cast<const float*>(lhs.vec));
  __m128 right = _mm_load_ps(reinterpret_cast<const float*>(rhs.vec));
  __m128 resultReg = _mm_mul_ps(left, right);
  alignas(16) float resultMem[4];
  _mm_store_ps(reinterpret_cast<float*>(resultMem), resultReg);
  return resultMem[0] + resultMem[1] + resultMem[2] + resultMem[3];
}
