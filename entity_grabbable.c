#include "entity.h"
#include "usersprite.h"
#include "global.h"

struct GrabbableObject {
  struct Object object;
  int grabbed;
};

void Grabbable_Move(struct CursorObject* cursor, int x, int y) {
  Transform_SetPosition(&(cursor->object.transform), (float)x, (float)y);
}

void Grabbable_onEvent() {
  struct GrabbableObject* grabbable = (struct GrabbableObject*)object;
  switch(Entity_GetEventType(event->type)) {
    case CURSOR_GRAB: {
      grabbable->grabbed = 1;
      break;
    }
    case CURSOR_MOVE: {
      if(grabbed) {
        int dx = (int)event->user.data1;
        int dy = (int)event->user.data2;
        Grabbable_Move(grabbable, dx, dy);
      }
      break;
    }
    case CURSOR_DROP: {
      grababble->grabbed = 0;
      break;
    }
    default: {}
  }
}

struct Object* Entity_Create_Grabble() {
  struct GrabbableObject* grabbable = (struct CursorObject*)Object_Create(sizeof(struct GrabbableObject));
  grabbable->object.flag.render = 1;
  grabbable->object.onEvent = Grabbable_onEvent;

  grabbable->grabbed = 0;

  Transform_SetPosition(&grabbable->object.transform, 100.0f, 100.0f);

  return cursor;
}
