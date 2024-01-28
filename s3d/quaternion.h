#pragma once
#include "vector3.h"

class Quaternion
{
public:
  float i, j, k, r;
  static Quaternion identity;

  /**
   * @brief Construct a new Quaternion object
   *
   * @param r real part of quaternion
   * @param i imaginary-i part of quaternion
   * @param j imaginary-j part of quaternion
   * @param k imaginary-k part of quaternion
   */
  Quaternion(float r, float i, float j, float k);
  Quaternion();

  static Quaternion fromAxisAngle(Vector3 axis, float angle);
  static Quaternion fromEulerAngles(float x, float y, float z);
  static Quaternion fromEulerAngles(Vector3 angles);
  static Quaternion slerp(Quaternion *q1, Quaternion *q2, float t);

  float toAxisAngle(Vector3 *axis);
  Vector3 toEulerAngles();
  Quaternion operator-();
  Quaternion operator~();
  Quaternion operator+(Quaternion *q);
  Quaternion operator-(Quaternion *q);
  Quaternion operator*(Quaternion *q);
  Vector3 operator*(Vector3 *v);
  Quaternion operator*(float v);
  float magnitude();
  Quaternion normalize();
  std::string toString();
};
