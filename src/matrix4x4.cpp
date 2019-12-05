#include "matrix4x4.hpp"

#include <immintrin.h>
#include <xmmintrin.h>

Matrix4x4::Matrix4x4() noexcept 
  : row{ Vector4f(), Vector4f(), Vector4f(), Vector4f() } {}

Matrix4x4::Matrix4x4(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3) noexcept 
  : row{ row0, row1, row2, row3 } {}

const Vector4f& Matrix4x4::operator[](const size_t idx) const noexcept {
  return row[idx];
}

Vector3f Multiply(const Vector3f& vec, const Matrix4x4& matrix) noexcept {
  matrix.operator[](0);
  return {
    vec.x * matrix[0][0] + vec.y * matrix[1][0] + vec.z * matrix[2][0] + matrix[3][0],
    vec.x * matrix[0][1] + vec.y * matrix[1][1] + vec.z * matrix[2][1] + matrix[3][1],
    vec.x * matrix[0][2] + vec.y * matrix[1][2] + vec.z * matrix[2][2] + matrix[3][2],
  };
}

Vector3f MultiplySimd(const Vector3f& vec, const Matrix4x4& matrix) noexcept {
  __m256 row01Reg = _mm256_load_ps(reinterpret_cast<const float*>(&(matrix[0])));
  __m256 row23Reg = _mm256_load_ps(reinterpret_cast<const float*>(&(matrix[2])));
  __m256 multFactorFor01 = _mm256_set_ps(vec.x, vec.x, vec.x, vec.x, vec.y, vec.y, vec.y, vec.y);
  __m256 multFactorFor23 = _mm256_set_ps(vec.z, vec.z, vec.z, vec.z, 1.0f, 1.0f, 1.0f, 1.0f);
  row01Reg = _mm256_mul_ps(row01Reg, multFactorFor01);
  row23Reg = _mm256_mul_ps(row23Reg, multFactorFor23);
  __m256 resultReg = _mm256_add_ps(row01Reg, row23Reg);
  alignas(32) float resultMem[8];
  _mm256_store_ps(reinterpret_cast<float*>(resultMem), resultReg);
  return Vector3f(resultMem[0] + resultMem[4], resultMem[1] + resultMem[5], resultMem[2] + resultMem[6]);
}
