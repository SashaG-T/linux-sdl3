#include "transform.h"

void Transform_Init(struct Transform* transform) {
  transform->localPosition = (struct Vector){0.0f, 0.0f};
  transform->position = (struct Vector){0.0f, 0.0f};
  transform->localRotation = 0.0f;
  transform->rotation = 0.0f;
  transform->dirty = 0;
}

void Transform_Recalculate(struct Transform* transform, struct Transform* parent) {
  if(parent) {
    struct Vector t;
    Vector_Rotate(&transform->localPosition, parent->rotation, &t);
    Vector_Add(&t, &parent->position, &transform->position);
    transform->rotation = parent->rotation + transform->localRotation;
  } else {
    transform->position = transform->localPosition;
    transform->rotation = transform->localRotation;
  }
}

void Transform_Translate(struct Transform* transform, float x, float y) {
  struct Vector t = {x, y};
  Vector_Rotate(&t, -(transform->rotation - transform->localRotation), &t);
  Vector_Add(&transform->localPosition, &t, &transform->localPosition);
  transform->dirty = 1;
}

void Transform_Rotate(struct Transform* transform, float r) {
  transform->localRotation += r;
  transform->dirty = 1;
}

void Transform_SetRotation(struct Transform* transform, float r) {
  transform->localRotation = r - transform->rotation;
  transform->dirty = 1;
}

void Transform_LocalTranslate(struct Transform* transform, float x, float y) {
  transform->localPosition.x += x;
  transform->localPosition.y += y;
  transform->dirty = 1;
}

void Transform_GetPosition(struct Transform* transform, struct Vector* out) {
  out->x = transform->position.x;
  out->y = transform->position.y;
}

void Transform_SetLocalPosition(struct Transform* transform, float x, float y) {
  transform->localPosition.x = x;
  transform->localPosition.y = y;
  transform->dirty = 1;
}

void Transform_SetPosition(struct Transform* transform, float x, float y) {
  float dx = x - transform->position.x;
  float dy = y - transform->position.y;
  Transform_Translate(transform, dx, dy);
}

float Transform_GetRotation(struct Transform* transform, float* out) {
  *out = transform->rotation;
}

void Transform_GetLocalPosition(struct Transform* transform, struct Vector* out) {
  out->x = transform->localPosition.x;
  out->y = transform->localPosition.y;
}

float Transform_GetLocalRotation(struct Transform* transform, float* out) {
  *out = transform->localRotation;
}

