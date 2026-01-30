#include "array.h"

#include <stdio.h>
#include <stdlib.h>

void Array_Init_Void(Array_void_t* array, unsigned int elementSize, unsigned int capacity) {
  array->size = 0;
  array->eSize = elementSize;
  array->start = 0;
  array->end = 0;
  Array_SetCapacity_Void(array, capacity);
}

void Array_Destroy_Void(Array_void_t* array) {
  free(array->start);
  array->size = 0;
  array->cap = 0;
  array->start = 0;
  array->end = 0;
  array->eSize = 0;
}

void Array_SetCapacity_Void(Array_void_t* array, unsigned int capacity) {
  unsigned int endOffset = array->end - array->start;
  unsigned int newSize = endOffset / array->eSize;
  array->cap = capacity;
  unsigned int bytes = array->eSize * (capacity + 1); //+1 since we use the last entry for pop
  array->start = realloc(array->start, bytes);
/* This should never happen... leaving so I remember this odd edge case though.
  if(bytes == 0) { //handle edge case where realloc _may_ return a zero-sized ptr.
    free(array->start);
    array->start = 0;
  }
*/
  array->end = array->start + endOffset; //end will point to "pop"'d value. (but also the element 1 past the end of the array)
  array->size = newSize < array->size ? newSize : array->size;
}

void* Array_Expand_Void(Array_void_t* array) {
  if(array->size == array->cap) {
    Array_SetCapacity_Void(array, array->cap?array->cap*2:1);
  }
  void* ret = array->end;
  array->end += array->eSize;
  array->size++;
  return ret;
}

void* Array_Shrink_Void(Array_void_t* array) {
  if(array->size == 0) {
    return array->end;
  }
  unsigned int halfCap = (array->cap >> 1);
  if(array->size <= halfCap) {
    Array_SetCapacity_Void(array, halfCap);
  }
  array->end -= array->eSize;
  array->size--;
  return array->end;
}

#include "unittest.h"

ARRAY_DECL(int)

UNITTEST_IMPL(array_create) {
  Array_int_t array;
  Array_Init(array, int, 0);
  
  UNITTEST_ASSERT(array.start != 0);
  UNITTEST_ASSERT(array.end == array.start);
  UNITTEST_ASSERT(array.size == 0);
  UNITTEST_ASSERT(array.eSize == sizeof(int));
  UNITTEST_ASSERT(array.cap == 0);

  Array_Destroy(array);
}

UNITTEST_IMPL(array_expand) {
  Array_int_t array;
  Array_Init(array, int, 0);

  int* ptr = Array_Expand(array);
  UNITTEST_ASSERT(array.start == ptr);
  UNITTEST_ASSERT(array.cap == 1);
  
  ptr = Array_Expand(array);
  UNITTEST_ASSERT(&array.start[1] == ptr);
  UNITTEST_ASSERT(array.cap == 2);

  ptr = Array_Expand(array);
  UNITTEST_ASSERT(&array.start[2] == ptr);
  UNITTEST_ASSERT(array.cap == 4);

  ptr = Array_Expand(array);
  UNITTEST_ASSERT(&array.start[3] == ptr);
  UNITTEST_ASSERT(array.cap == 4);

  ptr = Array_Expand(array);
  UNITTEST_ASSERT(&array.start[4] == ptr);
  UNITTEST_ASSERT(array.cap == 8);

  Array_Destroy(array);
}

UNITTEST_IMPL(array_push) {
  Array_int_t array;
  Array_Init(array, int, 0);

  Array_Push(array, 1);
  Array_Push(array, 2);
  Array_Push(array, 3);
  Array_Push(array, 4);

  UNITTEST_ASSERT(array.start[0] == 1);
  UNITTEST_ASSERT(array.start[1] == 2);
  UNITTEST_ASSERT(array.start[2] == 3);
  UNITTEST_ASSERT(array.start[3] == 4);

  Array_Destroy(array);
}

UNITTEST_IMPL(array_destroy) {
  Array_int_t array;
  Array_Init(array, int, 0);

  Array_Push(array, 1);
  Array_Push(array, 2);
  Array_Push(array, 3);
  Array_Push(array, 4);

  Array_Destroy(array);

  UNITTEST_ASSERT(array.size == 0);
  UNITTEST_ASSERT(array.eSize == 0);
  UNITTEST_ASSERT(array.cap == 0);
  UNITTEST_ASSERT(array.start == 0);
  UNITTEST_ASSERT(array.end == 0);
}

UNITTEST_IMPL(array_shrink) {
  Array_int_t array;
  Array_Init(array, int, 0);
  int* ptr;

  Array_Push(array, 1);
  Array_Push(array, 2);
  Array_Push(array, 3);
  Array_Push(array, 4);

  ptr = Array_Shrink(array);
  UNITTEST_ASSERT(array.end == ptr);
  UNITTEST_ASSERT(*ptr == 4);

  ptr = Array_Shrink(array);
  UNITTEST_ASSERT(array.end == ptr);
  UNITTEST_ASSERT(*ptr == 3);

  ptr = Array_Shrink(array);
  UNITTEST_ASSERT(array.end == ptr);
  UNITTEST_ASSERT(*ptr == 2);

  ptr = Array_Shrink(array);
  UNITTEST_ASSERT(array.end == ptr);
  UNITTEST_ASSERT(*ptr == 1);

  ptr = Array_Shrink(array);
  UNITTEST_ASSERT(array.end == ptr);
  UNITTEST_ASSERT(*ptr == 1); //can't shrink anymore so it'll return the last pop
}

UNITTEST_IMPL(array_pop) {
  Array_int_t array;
  Array_Init(array, int, 0);
  int value;

  Array_Push(array, 1);
  Array_Push(array, 2);
  Array_Push(array, 3);
  Array_Push(array, 4);

  UNITTEST_ASSERT(array.size == 4);
  UNITTEST_ASSERT(array.cap == 4);

  value = Array_Pop(array);
  UNITTEST_ASSERT(value == 4);
  UNITTEST_ASSERT(array.size == 3);
  UNITTEST_ASSERT(array.cap == 4);

  value = Array_Pop(array);
  UNITTEST_ASSERT(value == 3);
  UNITTEST_ASSERT(array.size == 2);
  UNITTEST_ASSERT(array.cap == 4);

  value = Array_Pop(array);
  UNITTEST_ASSERT(value == 2);
  UNITTEST_ASSERT(array.size == 1);
  UNITTEST_ASSERT(array.cap == 2);

  value = Array_Pop(array);
  UNITTEST_ASSERT(value == 1);
  UNITTEST_ASSERT(array.size == 0);
  UNITTEST_ASSERT(array.cap == 1);

  value = Array_Pop(array);
  UNITTEST_ASSERT(value == 1);
  UNITTEST_ASSERT(array.size == 0);
  UNITTEST_ASSERT(array.cap == 0);
}

UNITTEST_IMPL(array_remove) {
  UNITTEST_ASSERT(0);
}

UNITTEST_IMPL(array_insert) {
  UNITTEST_ASSERT(0);
}
