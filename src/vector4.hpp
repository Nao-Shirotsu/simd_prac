#pragma once

#include <ostream>

struct alignas(16) Vector4f {
  Vector4f() noexcept;
  Vector4f(const float x_, const float y_, const float z_, const float w_) noexcept;

  const float& operator[](const size_t idx) const noexcept;

  //operator Vector3f() const noexcept;

  union {
    float vec[4];
    struct {
      float x, y, z, w;
    };
  };
};

bool operator==(const Vector4f& lhs, const Vector4f& rhs) noexcept;
std::ostream& operator<<(std::ostream& ost, const Vector4f& vec) noexcept;

float Dot4D(const Vector4f& lhs, const Vector4f& rhs) noexcept;

float Dot4DSimd(const Vector4f& lhs, const Vector4f& rhs) noexcept;
