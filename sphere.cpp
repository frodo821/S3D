#include <math.h>
#include "s3d/sphere.h"

S3DSphere::S3DSphere() : S3DObject()
{
  this->radius = 1;
}

S3DSphere::S3DSphere(Vector3 position, Quaternion rotation, Vector3 scale, float radius) : S3DObject(position, rotation, scale)
{
  this->radius = radius;
}

float S3DSphere::distanceTo(Vector3 *point)
{
  return (this->position - point).magnitude() - this->radius;
}

S3DColor S3DSphere::getColorAtNearestPoint(Vector3 *point)
{
  return S3DColor(1, 1, 1);
}

/**
 * @param origin origin of the ray
 * @param ray direction of the ray, must be normalized
 * @param out the point of intersection
 * @return float distance to the point of intersection or -1 if there is no intersection
 */
float S3DSphere::intersect(Vector3 *origin, Vector3 *ray, Vector3 *out)
{
  Vector3 toObject = position - origin;
  float sqrDistToCenter = toObject.sqrMagnitude();
  float b = toObject.dot(ray);
  float sqRad = radius * radius;

  // if the sphere is behind the ray, there is no intersection
  if (b < 0 && sqrDistToCenter > sqRad)
  {
    return -1;
  }

  float sqr = ray->sqrMagnitude();
  Vector3 prj = (*ray) * (b / sqr);
  Vector3 pp = prj - &toObject;

  // if the ray misses the sphere, there is no intersection
  if (pp.sqrMagnitude() > sqRad)
  {
    return -1;
  }

  Vector3 tmp;

  float t = sqrt(sqRad - pp.sqrMagnitude());
  if (sqrDistToCenter < sqRad)
  {
    tmp = (*ray) * t;
    tmp = pp + &tmp;
    *out = position + &tmp;
    return (*origin - out).magnitude();
  }

  tmp = (*ray) * t;
  tmp = pp - &tmp;
  *out = position + &tmp;
  return (*origin - out).magnitude();
}

Vector3 S3DSphere::getNormalAt(Vector3 *point)
{
  return ((*point) - (&position)).normalize();
}

std::string S3DSphere::typeName()
{
  return "S3DSphere";
}
