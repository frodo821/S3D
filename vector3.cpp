#include <math.h>
#include "s3d/vector3.h"

/**
 * @brief Construct a new Vector 3:: Vector 3 object
 *
 * @param x x element of new vector
 * @param y y element of new vector
 * @param z z element of new vector
 */
Vector3::Vector3(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3::Vector3(float x, float y) : Vector3(x, y, 0) {}
Vector3::Vector3() : Vector3(0, 0, 0) {}

Vector3 Vector3::operator+(Vector3 *v)
{
  return Vector3(x + v->x, y + v->y, z + v->z);
}

Vector3 Vector3::operator-(Vector3 *v)
{
  return Vector3(x - v->x, y - v->y, z - v->z);
}

Vector3 Vector3::operator-()
{
  return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float v)
{
  return Vector3(x * v, y * v, z * v);
}

Vector3 Vector3::operator*(Vector3 *v)
{
  return Vector3(x * v->x, y * v->y, z * v->z);
}

Vector3 Vector3::operator/(float v)
{
  return Vector3(x / v, y / v, z / v);
}

float Vector3::dot(Vector3 *v)
{
  return x * v->x + y * v->y + z * v->z;
}

Vector3 Vector3::cross(Vector3 *v)
{
  return Vector3(y * v->z - z * v->y, z * v->x - x * v->z, x * v->y - y * v->z);
}

float Vector3::sqrMagnitude()
{
  return x * x + y * y + z * z;
}

float Vector3::magnitude()
{
  return sqrt(sqrMagnitude());
}

Vector3 Vector3::normalize()
{
  float m = magnitude();
  return Vector3(x / m, y / m, z / m);
}

std::string Vector3::toString()
{
  return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
