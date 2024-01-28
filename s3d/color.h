#pragma once
#include <stdint.h>

class S3DColor
{
public:
  float r, g, b, a;
  S3DColor();
  S3DColor(float r, float g, float b);
  S3DColor(float r, float g, float b, float a);

  S3DColor operator+(S3DColor *color);
  S3DColor operator-(S3DColor *color);
  S3DColor operator*(float scalar);
  S3DColor operator*(S3DColor *color);
  S3DColor operator/(float scalar);
  S3DColor operator/(S3DColor *color);
  S3DColor blendAlpha(S3DColor *color);
  S3DColor blendAlpha(S3DColor *color, float alpha);
  uint16_t to565();
};
