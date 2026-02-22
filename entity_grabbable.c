#include "entity.h"
#include "usersprite.h"
#include "global.h"
#include "collision.h"

void Grabbable_Move(struct GrabbableObject* grabbable, int x, int y) {
  Transform_SetPosition(&(grabbable->object.transform), (float)x - (grabbable->width / 2), (float)y - (grabbable->height / 2));
}

void Grabbable_onEvent() {
  struct GrabbableObject* grabbable = (struct GrabbableObject*)object;
  switch(Entity_GetEventType(event->type)) {
    case CURSOR_GRAB: {
      if(!grabbable->isGrabbable) {
        break;
      }
      int dx = *(float*)(event->user.data1);
      int dy = *(float*)(event->user.data2);
      struct Vector* p = &(grabbable->object.transform.position);
      grabbable->grabbed = Collision_PointInAABB(dx, dy, p->x, p->y, grabbable->width, grabbable->height);
      if(grabbable->grabbed && grabbable->onGrab) {
        grabbable->onGrab();
      }
      break;
    }
    case CURSOR_MOVE: {
      if(grabbable->grabbed) {
        int dx = *(float*)(event->user.data1);
        int dy = *(float*)(event->user.data2);
        Grabbable_Move(grabbable, dx, dy);
      }
      break;
    }
    case CURSOR_DROP: {
      if(grabbable->grabbed && grabbable->onDrop) {
        grabbable->onDrop();
      }
      grabbable->grabbed = 0;
      break;
    }
    case NON_USER_EVENT:
    default: {}
  }
}

void Entity_Init_Grabbable(struct GrabbableObject* grabbable, unsigned int width, unsigned int height) {
  grabbable->object.flag.render = 1;
  grabbable->object.onEvent = Grabbable_onEvent;
  grabbable->isGrabbable = 1;
  grabbable->grabbed = 0;
  grabbable->width = width;
  grabbable->height = height;
  grabbable->onGrab = 0;
  grabbable->onDrop = 0;
}


struct Object* Entity_Create_Grabbable(unsigned int width, unsigned   int height) {
  struct GrabbableObject* grabbable = (struct GrabbableObject*)Object_Create(sizeof(struct GrabbableObject));
  Entity_Init_Grabbable(grabbable, width, height);
  return (struct Object*)grabbable;
}
