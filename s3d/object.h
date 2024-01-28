#pragma once
#include "vector3.h"
#include "quaternion.h"
#include "color.h"
#include <vector>
#include <string>

class S3DObject
{
public:
  Vector3 position;
  Quaternion rotation;
  Vector3 scale;
  S3DObject *parent;
  std::vector<S3DObject *> *children;

  S3DObject();
  S3DObject(Vector3 position, Quaternion rotation, Vector3 scale);

  void translate(Vector3 *translation);
  void rotate(Quaternion *rotation);
  void rescale(Vector3 *scale);
  void transform(Vector3 *translation, Quaternion *rotation, Vector3 *scale);

  virtual float distanceTo(Vector3 *point) = 0;
  virtual S3DColor getColorAtNearestPoint(Vector3 *point) = 0;
  virtual float intersect(Vector3 *origin, Vector3 *ray, Vector3 *out) = 0;
  virtual Vector3 getNormalAt(Vector3 *point) = 0;
  virtual std::string toString();
  virtual std::string typeName();
};
