#include "array.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

ARRAY_TYPE(char) Array_tmp;

ARRAY_TYPE(char) Array_Create_Generic(unsigned int elementSize, unsigned int size) {
  ARRAY_TYPE(char) array;
  array.data = malloc(elementSize * size);
  array.eSize = elementSize;
  array.size = array.cap = size;
  return array;
}

void Array_SetCapacity_Generic(ARRAY_TYPE(char)* array, unsigned int capacity) {
  assert(array);
  assert(capacity > array->cap); //for now we can't shrink arrays....
  //copy over data
  char* data = malloc(array->eSize*capacity);
  memcpy(data, array->data, array->size*array->eSize);
  free(array->data);
  array->data = data;
  array->cap = capacity;
}

void Array_Push_Generic(ARRAY_TYPE(char)* array, ...) {
  assert(array);

  //if there's no room just double the available space.
  if(array->size == array->cap) {
    Array_SetCapacity_Generic(array, array->cap * 2);
  }

  va_list ap;


/*
  char t[array->eSize];
  va_start(ap, array);
  char* data = va_arg(ap, typeof(t));
  unsigned offset = array->size * array->eSize;
  for(int i = 0; i < array->eSize; i++) {
    array->data[offset + i] = data[i];
  }
*/

  for(int i = 0; i < array->eSize; i++) {
    unsigned char c = va_arg(ap, unsigned char);
    array->data[array->size * array->eSize + i] = c;
  }

  va_end(ap);
  array->size++;
}

#include "unittest.h"

ARRAY_DECL(int);

UNITTEST_IMPL(array_create) {
  ARRAY_TYPE(int) intArray = Array_Create(int, 10);
  for(int i = 0; i < 10; i++) {
    intArray.data[i] = i;
  }

  UNITTEST_ASSERT(intArray.data != 0);
  
  UNITTEST_ASSERT(intArray.data[0] == 0);
  UNITTEST_ASSERT(intArray.data[1] == 1);
  UNITTEST_ASSERT(intArray.data[2] == 2);
  UNITTEST_ASSERT(intArray.data[3] == 3);
  UNITTEST_ASSERT(intArray.data[4] == 4);
  UNITTEST_ASSERT(intArray.data[5] == 5);
  UNITTEST_ASSERT(intArray.data[6] == 6);
  UNITTEST_ASSERT(intArray.data[7] == 7);
  UNITTEST_ASSERT(intArray.data[8] == 8);
  UNITTEST_ASSERT(intArray.data[9] == 9);

  UNITTEST_ASSERT(intArray.eSize == sizeof(int));
  UNITTEST_ASSERT(intArray.size == 10);
  UNITTEST_ASSERT(intArray.cap == 10);
}

UNITTEST_IMPL(array_push) {
  ARRAY_TYPE(int) intArray = Array_Create(int, 1);
//  Array_Push(intArray, 45);

  Array_tmp=*((ARRAY_TYPE(char)*)(&intArray));

  Array_Push_Generic(

	(ARRAY_TYPE(char)*)(&Array_tmp)

	,intArray.eSize,45);


  //UNITTEST_ASSERT(intArray.data[3] == 45);
}
