#pragma once

#include <ostream>

class alignas(16) Vector4f {
public:
  Vector4f();
  Vector4f(const float x_, const float y_, const float z_, const float w_);

  union {
    float vec[4];
    struct {
      float x, y, z, w;
    };
  };
};

bool operator==(const Vector4f& lhs, const Vector4f& rhs);
std::ostream& operator<<(std::ostream& ost, const Vector4f& vec);

float Dot(const Vector4f& lhs, const Vector4f& rhs);

float DotSimd(const Vector4f& lhs, const Vector4f& rhs);
