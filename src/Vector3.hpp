#include <ostream>

// 普通の3次元ベクトルクラス
class Vector3f {
public:
  Vector3f();
  Vector3f(const float x_, const float y_, const float z_);

  float x, y, z;
};

bool operator==(const Vector3f& lhs, const Vector3f& rhs);
std::ostream& operator<<(std::ostream& ost, const Vector3f& vec);

float Dot(const Vector3f& lhs, const Vector3f& rhs);

float DotSimd(const Vector3f& lhs, const Vector3f& rhs);

Vector3f Cross(const Vector3f& lhs, const Vector3f& rhs);

Vector3f CrossSimd(const Vector3f& lhs, const Vector3f& rhs);