#include "Vector3.hpp"

#include <immintrin.h>
#include <xmmintrin.h>
#include <iostream>

Vector3f::Vector3f() = default;

Vector3f::Vector3f(const float x_, const float y_, const float z_) 
  : x(x_)
  , y(y_)
    , z(z_) {}

bool Vector3f::operator==(const Vector3f& other) {
  return (x == other.x && y == other.y && z == other.z);
}

std::ostream& operator<<(std::ostream& ost, const Vector3f& vec) {
  return ost << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

float Dot(const Vector3f& lhs, const Vector3f& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float DotSimd(const Vector3f& lhs, const Vector3f& rhs) {
  __m128 left = _mm_set_ps(0.0f, lhs.x, lhs.y, lhs.z);
  __m128 right = _mm_set_ps(0.0f, rhs.x, rhs.y, rhs.z);

  __m128 resultReg = _mm_mul_ps(left, right);
  float resultMem[4];
  _mm_store_ps(reinterpret_cast<float*>(resultMem), resultReg);
  return resultMem[2] + resultMem[1] + resultMem[0];
}
//
//Vector3 Cross(const Vector3& lhs, const Vector3& rhs) {
//  return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
//                 lhs.z * rhs.x - lhs.x * rhs.z,
//                 lhs.x * rhs.y - lhs.y * rhs.x);
//}
//
//Vector3 CrossSimd(const Vector3& lhs, const Vector3& rhs) {
//  float* leftPPYZXZXY = new float[8];
//  leftPPYZXZXY[0] = 0;
//  leftPPYZXZXY[1] = 0;
//  leftPPYZXZXY[2] = lhs.y;
//  leftPPYZXZXY[3] = lhs.z;
//  leftPPYZXZXY[4] = lhs.x;
//  leftPPYZXZXY[5] = lhs.z;
//  leftPPYZXZXY[6] = lhs.x;
//  leftPPYZXZXY[7] = lhs.y;
//
//  float* rightPPZXYYZX = new float[8];
//  rightPPZXYYZX[0] = 0;
//  rightPPZXYYZX[1] = 0;
//  rightPPZXYYZX[2] = rhs.z;
//  rightPPZXYYZX[3] = rhs.x;
//  rightPPZXYYZX[4] = rhs.y;
//  rightPPZXYYZX[5] = rhs.y;
//  rightPPZXYYZX[6] = rhs.z;
//  rightPPZXYYZX[7] = rhs.x;
//
//  __m256 left = _mm256_load_ps(leftPPYZXZXY);
//  __m256 right = _mm256_load_ps(rightPPZXYYZX);
//  __m256 mulResult = _mm256_mul_ps(left, right);
//
//  delete[] leftPPYZXZXY;
//  delete[] rightPPZXYYZX;
//  return Vector3(0, 0, 0);
//}
