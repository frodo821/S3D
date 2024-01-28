#pragma once
#include <string>

class Vector3
{
public:
  float x, y, z;
  Vector3();
  Vector3(float x, float y);
  Vector3(float x, float y, float z);
  Vector3 operator+(Vector3 *v);
  Vector3 operator-(Vector3 *v);
  Vector3 operator-();
  Vector3 operator*(float f);
  Vector3 operator*(Vector3 *v);
  Vector3 operator/(float f);
  float dot(Vector3 *v);
  Vector3 cross(Vector3 *v);
  float magnitude();
  float sqrMagnitude();
  Vector3 normalize();
  std::string toString();
};
