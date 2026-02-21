#include "object.h"
#include <stdlib.h>
#include <stdio.h>

int _nextId = 0;
struct Object* rootObjPtr = 0;
struct Object* object = 0;
SDL_Event* event;
struct List nonParentedObjectList;

void defaultUpdate() {
  Object_PrintDebugInfo(object);
}

void Object_InitRoot() {
  if(rootObjPtr) {
    return;
  } 
  List_Init(&nonParentedObjectList);
  rootObjPtr = Object_Create(sizeof(struct Object));
}

void Object_AddNewObjects() {
  if(!rootObjPtr) {
    return;
  }
  List_AppendList(&rootObjPtr->childList, &nonParentedObjectList);
  List_Init(&nonParentedObjectList);
}

void Object_Init(struct Object* object) {
  object->id = _nextId++;
  Transform_Init(&object->transform);
  object->flag.destroy = 0;
  object->flag.render  = 0;
  List_Init(&object->childList);
  object->newParent = 0;
  object->update = 0; //defaultUpdate;
  object->render = 0;
  object->destroy = 0;
  object->onEvent = 0;
}

struct Object* Object_Create(size_t size) {
  struct Object* objectPtr = malloc(size);
  Object_Init(objectPtr);
  if(rootObjPtr) {
    objectPtr->newParent = rootObjPtr;
    List_Append(&nonParentedObjectList, (struct LNode*)objectPtr);
  } else {
    objectPtr->secret = 42;
  }
  return objectPtr;
}

void Object_Destroy(struct Object* objectPtr) {
  if(objectPtr->destroy) {
    object = objectPtr;
    objectPtr->destroy();
  }
  free(objectPtr);
}

void Object_ResolveReparenting_RemoveFromTree(struct Object* parent) {
  struct Object* currObjPtr = 0;
  while(currObjPtr = (struct Object*)List_GetNext(&parent->childList, (struct LNode*)currObjPtr)) {
    if(currObjPtr->newParent) {
      List_Remove(&parent->childList, (struct LNode*)currObjPtr);
      List_Append(&nonParentedObjectList, (struct LNode*)currObjPtr);
    }
    Object_ResolveReparenting_RemoveFromTree(currObjPtr);
  }
}

void Object_ResolveReparenting_AddToTree() {
  struct Object* currObjPtr = 0;
  while(currObjPtr = (struct Object*)List_GetNext(&nonParentedObjectList, (struct LNode*)currObjPtr)) {
    List_Append(&currObjPtr->newParent->childList, (struct LNode*)currObjPtr);
    currObjPtr->newParent = 0;
    currObjPtr->transform.dirty = 1;
  }
  List_Init(&nonParentedObjectList);
}

void Object_ResolveReparenting() {
  Object_ResolveReparenting_RemoveFromTree(rootObjPtr);
  Object_ResolveReparenting_AddToTree();
}

void Object_SetParent(struct Object* objectPtr, struct Object* parent) {
  objectPtr->newParent = parent ? parent : rootObjPtr;
}

void Object_PrintDebugInfo(struct Object* object) {
  printf("Object: %d\n", object->id);
}
