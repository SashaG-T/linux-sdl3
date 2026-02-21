#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "object.h"

enum EntityEventType {
  CURSOR_GRAB,
  CURSOR_DROP,
  ENTITY_EVENT_TYPE_COUNT
}

struct Object* Entity_Create_Cursor();
struct Object* Entity_Create_Grabbable();

void Entity_RegisterEvents();
int Entity_GetEventType(int eventType);
void Entity_PushEvent(enum EntityEventType type, int code, void* data1, void* data2);

#endif
