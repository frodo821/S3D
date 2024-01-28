#pragma once
#include "object.h"
#include "color.h"

class S3DSphere : public S3DObject
{
public:
  float radius;

  S3DSphere();
  S3DSphere(Vector3 position, Quaternion rotation, Vector3 scale, float radius);

  float distanceTo(Vector3 *point) override;
  S3DColor getColorAtNearestPoint(Vector3 *point) override;
  float intersect(Vector3 *origin, Vector3 *ray, Vector3 *out) override;
  Vector3 getNormalAt(Vector3 *point) override;
  std::string typeName() override;
};
