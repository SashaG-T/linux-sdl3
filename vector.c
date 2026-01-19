#include "vector.h"
#include <math.h>

void Vector_Add(struct Vector* a, struct Vector* b, struct Vector* out) {
  out->x = a->x + b->x;
  out->y = a->y + b->y;
}

void Vector_Sub(struct Vector* a, struct Vector* b, struct Vector* out) {
  out->x = a->x - b->x;
  out->y = a->y - b->y;
}

void Vector_Scale(struct Vector* a, float k, struct Vector* out) {
  out->x = a->x * k;
  out->y = a->y * k;
}

void Vector_Mul(struct Vector* a, struct Vector* b, struct Vector* out) {
  out->x = a->x * b->x;
  out->y = a->y * b->y;
}

float Vector_Length(struct Vector* a) {
  return sqrt(a->x*a->x + a->y*a->y);
}

void Vector_Normalize(struct Vector* a, struct Vector* out) {
  float length = Vector_Length(a);
  Vector_Scale(a, length, out);
}

void Vector_Rotate(struct Vector* a, float r, struct Vector* out) {
  r *= 3.14159f / 180.0f;
  float sr = sin(r);
  float cr = cos(r);
  float x = a->x;
  float y = a->y;
  out->x = x * cr - y * sr;
  out->y = x * sr + y * cr;
}
