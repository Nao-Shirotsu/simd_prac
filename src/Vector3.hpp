#include <ostream>

// ���ʂ�3�����x�N�g���N���X
class Vector3f {
public:
  Vector3f();
  Vector3f(const float x_, const float y_, const float z_);

  bool operator==(const Vector3f& other);

  float x, y, z;
};

std::ostream& operator<<(std::ostream& ost, const Vector3f& vec);

float Dot(const Vector3f& lhs, const Vector3f& rhs);

float DotSimd(const Vector3f& lhs, const Vector3f& rhs);

// �x�N�g���̊O�� ���ʃo�[�W����
//Vector3f Cross(const Vector3f& lhs, const Vector3f& rhs);
//
//Vector3f CrossSimd(const Vector3f& lhs, const Vector3f& rhs);