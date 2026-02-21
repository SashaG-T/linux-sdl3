#include "entity.h"
#include "usersprite.h"
#include "global.h"
#include "collision.h"

struct GrabbableObject {
  struct Object object;
  int grabbed;
  int width, height;
};

void Grabbable_Move(struct GrabbableObject* grabbable, int x, int y) {
  Transform_SetPosition(&(grabbable->object.transform), (float)x - (grabbable->width / 2), (float)y - (grabbable->height / 2));
}

void Grabbable_onEvent() {
  struct GrabbableObject* grabbable = (struct GrabbableObject*)object;
  switch(Entity_GetEventType(event->type)) {
    case CURSOR_GRAB: {
      int dx = *(float*)(event->user.data1);
      int dy = *(float*)(event->user.data2);
      struct Vector* p = &(grabbable->object.transform.position);
      grabbable->grabbed = Collision_PointInAABB(dx, dy, p->x, p->y, grabbable->width, grabbable->height);
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
      grabbable->grabbed = 0;
      break;
    }
    case NON_USER_EVENT:
    default: {}
  }
}

struct Object* Entity_Create_Grabbable(unsigned int width, unsigned   int height) {
  struct GrabbableObject* grabbable = (struct GrabbableObject*)Object_Create(sizeof(struct GrabbableObject));
  grabbable->object.flag.render = 1;
  grabbable->object.onEvent = Grabbable_onEvent;
  grabbable->grabbed = 0;
  grabbable->width = width;
  grabbable->height = height;

  return (struct Object*)grabbable;
}
