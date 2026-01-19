#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "vector.h"

struct Transform {
  struct Vector localPosition;
  struct Vector position;
  float localRotation;
  float rotation;
  int dirty;
};

void Transform_Init(struct Transform* transform);

void Transform_Recalculate(struct Transform* transform, struct Transform* parent);
void Transform_Translate(struct Transform* transform, float x, float y);
void Transform_Rotate(struct Transform* transform, float r);
void Transform_LocalTranslate(struct Transform* transform, float x, float y);
void Transform_GetPosition(struct Transform* transform, struct Vector* out);
float Transform_GetRotation(struct Transform* transform, float* out);
void Transform_GetLocalPosition(struct Transform* transform, struct Vector* out);
float Transform_GetLocalRotation(struct Transform* transform, float* out);

#endif
