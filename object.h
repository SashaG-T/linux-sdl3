#ifndef OBJECT_H_
#define OBJECT_H_

#include "list.h"
#include "transform.h"
#include <stdlib.h>
#include <SDL3/SDL.h>

struct Object {
  struct LNode node;
  struct List childList;
  int id;
  int secret;
  struct Transform transform;
  struct Flags {
    unsigned destroy 	: 1;
    unsigned render  	: 1;
  } flag;
  struct Object* newParent;
  void (*update)();
  void (*render)();
  void (*destroy)();
  void (*onEvent)();
};

extern struct Object* rootObjPtr;
extern struct Object* object;
extern SDL_Event* event;

void Object_InitRoot();
void Object_AddNewObjects();
void Object_ResolveReparenting();
struct Object* Object_Create(size_t size);
void Object_Destroy(struct Object* object);

void Object_SetParent(struct Object* objectPtr, struct Object* parent);

void Object_PrintDebugInfo(struct Object* object);

#endif

