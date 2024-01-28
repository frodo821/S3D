#include "s3d/object.h"

S3DObject::S3DObject() : S3DObject(Vector3(0, 0, 0), Quaternion(1, 0, 0, 0), Vector3(1, 1, 1))
{
}

S3DObject::S3DObject(Vector3 position, Quaternion rotation, Vector3 scale)
{
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
  this->parent = NULL;
  this->children = new std::vector<S3DObject *>();
}

void S3DObject::translate(Vector3 *translation)
{
  this->position = this->position + translation;

  for (int i = 0; i < this->children->size(); i++)
  {
    this->children->at(i)->translate(translation);
  }
}

void S3DObject::rotate(Quaternion *rotation)
{
  this->rotation = this->rotation * rotation;

  for (int i = 0; i < this->children->size(); i++)
  {
    this->children->at(i)->rotate(rotation);
    this->children->at(i)->position = (*rotation) * (&(this->children->at(i)->position));
  }
}

void S3DObject::rescale(Vector3 *scale)
{
  this->scale = this->scale * scale;

  for (int i = 0; i < this->children->size(); i++)
  {
    this->children->at(i)->rescale(scale);
    this->children->at(i)->position = this->children->at(i)->position * scale;
  }
}

void S3DObject::transform(Vector3 *translation, Quaternion *rotation, Vector3 *scale)
{
  this->translate(translation);
  this->rotate(rotation);
  this->rescale(scale);
}

std::string S3DObject::typeName()
{
  return "S3DObject";
}

std::string S3DObject::toString()
{
  return this->typeName() + "(" + this->position.toString() + ", " + this->rotation.toString() + ", " + this->scale.toString() + ")";
}
