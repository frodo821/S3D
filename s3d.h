#pragma once
#include <TFT_eSPI.h>
#include <vector>
#include "s3d/object.h"
#include "s3d/color.h"
#include "s3d/vector3.h"
#include "s3d/quaternion.h"
#include "s3d/sphere.h"

typedef struct
{
  Vector3 position;
  Vector3 forward;
  Vector3 up;

  float targetDepth;
  float fov;
} S3DCamera_t;

typedef struct
{
  Vector3 direction;
  float intensity;
  S3DColor color;
} S3DLight_t;

class S3D
{
private:
  TFT_eSPI *tft;
  TFT_eSprite *screen;
  std::vector<S3DObject *> *renderer;
  S3DColor backgroundColor;
  S3DColor colorAtPixel(int x, int y);
  Vector3 *screenResolution;

public:
  S3DCamera_t camera;
  S3DLight_t globalLight;
  S3D();
  S3D(TFT_eSPI *tft);

  void render();
  void clearScreen();
  void update();
  void addObject(S3DObject *object);
  void removeObject(S3DObject *object);
  void clearObjects();

  void setBackgroundColor(S3DColor color);
  void blitz(TFT_eSprite *sprite, int x, int y);
  S3DColor getBackgroundColor();
  TFT_eSprite *getScreen();
};
