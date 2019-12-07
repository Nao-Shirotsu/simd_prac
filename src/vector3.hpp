#pragma once

#include <ostream>

struct Vector3f {
  Vector3f() noexcept;
  Vector3f(const float x_, const float y_, const float z_) noexcept;

  float x, y, z;
};

bool operator==(const Vector3f& lhs, const Vector3f& rhs) noexcept;
std::ostream& operator<<(std::ostream& ost, const Vector3f& vec) noexcept;

float Dot3D(const Vector3f& lhs, const Vector3f& rhs) noexcept;

float Dot3DSimd(const Vector3f& lhs, const Vector3f& rhs) noexcept;

Vector3f Cross3D(const Vector3f& lhs, const Vector3f& rhs) noexcept;

Vector3f Cross3DSimd(const Vector3f& lhs, const Vector3f& rhs) noexcept;