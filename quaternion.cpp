#include <math.h>
#include "s3d/quaternion.h"

Quaternion Quaternion::identity = Quaternion();

Quaternion::Quaternion()
{
  this->r = 1;
  this->i = 0;
  this->j = 0;
  this->k = 0;
}

Quaternion::Quaternion(float r, float i, float j, float k)
{
  this->r = r;
  this->i = i;
  this->j = j;
  this->k = k;
}

Quaternion Quaternion::fromAxisAngle(Vector3 axis, float angle)
{
  float halfAngle = angle / 2;
  float sinHalfAngle = sin(halfAngle);
  return Quaternion(cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

Quaternion Quaternion::fromEulerAngles(float x, float y, float z)
{
  float halfX = x / 2;
  float halfY = y / 2;
  float halfZ = z / 2;
  float sinHalfX = sin(halfX);
  float sinHalfY = sin(halfY);
  float sinHalfZ = sin(halfZ);
  float cosHalfX = cos(halfX);
  float cosHalfY = cos(halfY);
  float cosHalfZ = cos(halfZ);
  return Quaternion(cosHalfX * cosHalfY * cosHalfZ + sinHalfX * sinHalfY * sinHalfZ,
                    sinHalfX * cosHalfY * cosHalfZ - cosHalfX * sinHalfY * sinHalfZ,
                    cosHalfX * sinHalfY * cosHalfZ + sinHalfX * cosHalfY * sinHalfZ,
                    cosHalfX * cosHalfY * sinHalfZ - sinHalfX * sinHalfY * cosHalfZ);
}

Quaternion Quaternion::fromEulerAngles(Vector3 angles)
{
  return fromEulerAngles(angles.x, angles.y, angles.z);
}

Quaternion Quaternion::slerp(Quaternion *q1, Quaternion *q2, float t)
{
  float dot = q1->r * q2->r + q1->i * q2->i + q1->j * q2->j + q1->k * q2->k;
  float theta = acos(dot) * t;
  Quaternion tmp = (*q1) * dot;
  Quaternion qperp = (*q2) - &tmp;
  qperp = qperp.normalize();
  tmp = qperp * sin(theta);
  return (*q1) * cos(theta) + &tmp;
}

Quaternion Quaternion::operator-()
{
  return Quaternion(-r, -i, -j, -k);
}

Quaternion Quaternion::operator~()
{
  return Quaternion(r, -i, -j, -k);
}

Quaternion Quaternion::operator+(Quaternion *q)
{
  return Quaternion(r + q->r, i + q->i, j + q->j, k + q->k);
}

Quaternion Quaternion::operator-(Quaternion *q)
{
  return Quaternion(r - q->r, i - q->i, j - q->j, k - q->k);
}

Quaternion Quaternion::operator*(Quaternion *q)
{
  return Quaternion(
      r * q->r - i * q->i - j * q->j - k * q->k,
      i * q->r + j * q->k - k * q->j + r * q->i,
      j * q->r + k * q->i + r * q->j - i * q->k,
      k * q->r + r * q->k + i * q->j - j * q->i);
}

Vector3 Quaternion::operator*(Vector3 *v)
{
  Quaternion t = normalize();
  Quaternion qv = Quaternion(0, v->x, v->y, v->z);
  Quaternion invT = ~t;
  Quaternion q = t * (&qv) * (&invT);

  return Vector3(q.i, q.j, q.k);
}

Quaternion Quaternion::operator*(float v)
{
  return Quaternion(r * v, i * v, j * v, k * v);
}

float Quaternion::magnitude()
{
  return sqrt(r * r + i * i + j * j + k * k);
}

Quaternion Quaternion::normalize()
{
  float m = magnitude();
  return Quaternion(r / m, i / m, j / m, k / m);
}

std::string Quaternion::toString()
{
  return std::to_string(r) + " + " + std::to_string(i) + "i + " + std::to_string(j) + "j + " + std::to_string(k) + "k";
}
