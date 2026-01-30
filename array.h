#ifndef ARRAY_H_
#define ARRAY_H_

#define ARRAY_DECL(type) \
typedef struct Array_ ## type { \
  unsigned int size; \
  unsigned int cap; \
  unsigned int eSize; \
  type* end; \
  type* start; \
} Array_ ## type ## _t;

ARRAY_DECL(void)

void Array_Init_Void(Array_void_t* array, unsigned int elementSize, unsigned int size);
void Array_SetCapacity_Void(Array_void_t* array, unsigned int capacity);
void Array_Destroy_Void(Array_void_t* array);
void* Array_Expand_Void(Array_void_t* array);
void* Array_Shrink_Void(Array_void_t* array);

#define Array_Init(array, type, size) (Array_Init_Void((Array_void_t*)(&(array)), sizeof(type), size))
#define Array_Expand(array) ((typeof((array).start))Array_Expand_Void((Array_void_t*)(&(array))))
#define Array_Push(array, value) (*Array_Expand(array)=value)
#define Array_Destroy(array) (Array_Destroy_Void((Array_void_t*)(&(array))))
#define Array_Shrink(array) ((typeof((array).start))Array_Shrink_Void((Array_void_t*)(&(array))))
#define Array_Pop(array) (*Array_Shrink(array))

#endif
