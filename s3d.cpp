#include "s3d.h"
#include "Arduino.h"

S3D::S3D() {}
S3D::S3D(TFT_eSPI *tft)
{
  this->tft = tft;
  this->screen = new TFT_eSprite(tft);
  this->renderer = new std::vector<S3DObject *>();
  this->backgroundColor = S3DColor(0, 0, 0);
  this->screenResolution = new Vector3(tft->width(), tft->height());
  this->camera = {
      Vector3(0, 0, 2),
      Vector3(0, 0, -1),
      Vector3(0, 1, 0),
      1,
      40};
  this->globalLight = {
      Vector3(
          0.666666667f,
          0.666666667f,
          0.333333333f),
      1,
      S3DColor(1, 1, 1)};
  this->screen->setColorDepth(8);
  this->screen->createSprite(240, 240);
}

S3DColor S3D::colorAtPixel(int x, int y)
{
  Vector3 temp;
  Vector3 p = (Vector3(x, y) * 2 - this->screenResolution) / min(this->screenResolution->x, this->screenResolution->y);
  Vector3 side = this->camera.forward.cross(&this->camera.up);
  float fov = this->camera.fov / RAD_TO_DEG;
  float sr = sin(fov);
  temp = this->camera.forward * this->camera.targetDepth * cos(fov);
  temp = this->camera.up * p.y * sr + &temp;
  Vector3 ray = (side * p.x * sr + &temp).normalize();

  float closest = 1000000;
  S3DObject *closestObject = NULL;
  Vector3 intersection;

  for (int i = 0; i < this->renderer->size(); i++)
  {
    S3DObject *object = this->renderer->at(i);
    float distance = object->intersect(&this->camera.position, &ray, &temp);
    if (distance > 0 && distance < closest)
    {
      closest = distance;
      closestObject = object;
      intersection = temp;
    }
  }

  if (closestObject != NULL)
  {
    auto c = closestObject->getColorAtNearestPoint(&intersection);
    auto n = closestObject->getNormalAt(&intersection);
    float light = max(0.16f, n.dot(&this->globalLight.direction)) * this->globalLight.intensity;
    auto lc = this->globalLight.color * light;

    return S3DColor(c.r * lc.r, c.g * lc.g, c.b * lc.b);
  }
  else
  {
    return this->backgroundColor;
  }
}

void S3D::update()
{
  for (int x = 0; x < this->screenResolution->x; x++)
  {
    for (int y = 0; y < this->screenResolution->y; y++)
    {
      this->screen->drawPixel(x, y, this->colorAtPixel(this->screenResolution->x - x - 1, this->screenResolution->y - y - 1).to565());
    }
  }
  this->screen->pushSprite(0, 0);
  this->screen->fillSprite(this->backgroundColor.to565());
}

void S3D::addObject(S3DObject *object)
{
  this->renderer->push_back(object);
}

void S3D::removeObject(S3DObject *object)
{
  for (int i = 0; i < this->renderer->size(); i++)
  {
    if (this->renderer->at(i) == object)
    {
      this->renderer->erase(this->renderer->begin() + i);
      return;
    }
  }
}

void S3D::clearObjects()
{
  this->renderer->clear();
}

void S3D::setBackgroundColor(S3DColor color)
{
  this->backgroundColor = color;
}

S3DColor S3D::getBackgroundColor()
{
  return this->backgroundColor;
}

void S3D::blitz(TFT_eSprite *sprite, int x, int y)
{
  sprite->pushToSprite(screen, x, y);
}
