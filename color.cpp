#include "s3d/color.h"

inline float clamp01(float value)
{
  if (value < 0)
  {
    return 0;
  }
  else if (value > 1)
  {
    return 1;
  }
  else
  {
    return value;
  }
}

S3DColor::S3DColor() : S3DColor(0, 0, 0, 1) {}
S3DColor::S3DColor(float r, float g, float b) : S3DColor(r, g, b, 1) {}
S3DColor::S3DColor(float r, float g, float b, float a)
{
  this->r = clamp01(r);
  this->g = clamp01(g);
  this->b = clamp01(b);
  this->a = clamp01(a);
}

S3DColor S3DColor::operator+(S3DColor *color)
{
  return S3DColor(r + color->r, g + color->g, b + color->b, a + color->a);
}

S3DColor S3DColor::operator-(S3DColor *color)
{
  return S3DColor(r - color->r, g - color->g, b - color->b, a - color->a);
}

S3DColor S3DColor::operator*(float scalar)
{
  return S3DColor(r * scalar, g * scalar, b * scalar, a * scalar);
}

S3DColor S3DColor::operator*(S3DColor *color)
{
  return S3DColor(r * color->r, g * color->g, b * color->b, a * color->a);
}

S3DColor S3DColor::operator/(float scalar)
{
  return S3DColor(r / scalar, g / scalar, b / scalar, a / scalar);
}

S3DColor S3DColor::operator/(S3DColor *color)
{
  return S3DColor(r / color->r, g / color->g, b / color->b, a / color->a);
}

S3DColor S3DColor::blendAlpha(S3DColor *color)
{
  return blendAlpha(color, 1);
}

S3DColor S3DColor::blendAlpha(S3DColor *color, float alpha)
{
  float i = a + color->a;

  if (i == 0)
  {
    return S3DColor(0, 0, 0, 0);
  }

  return S3DColor(
      (r * a + color->r * color->a) / i,
      (g * a + color->g * color->a) / i,
      (b * a + color->b * color->a) / i,
      alpha);
}

uint16_t S3DColor::to565()
{
  uint16_t ir = (uint16_t)(r * 31);
  uint16_t ig = (uint16_t)(g * 63);
  uint16_t ib = (uint16_t)(b * 31);

  return (ir << 11) | (ig << 5) | ib;
}
