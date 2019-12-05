#pragma once

#include "vector4.hpp"
#include "vector3.hpp"

struct alignas(32) Matrix4x4 {
  Matrix4x4() noexcept;
  Matrix4x4(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3) noexcept;
  const Vector4f& operator[](const size_t idx) const noexcept;
  Vector4f row[4];
};

Vector3f Multiply(const Vector3f& vec, const Matrix4x4& matrix) noexcept;
Vector3f MultiplySimd(const Vector3f& vec, const Matrix4x4& matrix) noexcept;
