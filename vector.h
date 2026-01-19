#ifndef VECTOR_H_
#define VECTOR_H_

struct Vector {

  float x, y;

};

void Vector_Add(struct Vector* a, struct Vector* b, struct Vector* out);
void Vector_Sub(struct Vector* a, struct Vector* b, struct Vector* out);
void Vector_Scale(struct Vector* a, float k, struct Vector* out);
void Vector_Mul(struct Vector* a, struct Vector* b, struct Vector* out);
float Vector_Length(struct Vector* a);
void Vector_Normalize(struct Vector* a, struct Vector* out);
void Vector_Rotate(struct Vector*a, float r, struct Vector* out);

#endif
