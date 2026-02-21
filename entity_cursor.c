#include "entity.h"
#include "usersprite.h"
#include "global.h"

struct CursorObject {
  struct Object object;
  struct Sprite* sprite[6];
};

void Cursor_Move(struct CursorObject* cursor, int x, int y) {
  Transform_SetPosition(&(cursor->object.transform), (float)x, (float)y);
}

void Cursor_onEvent() {
  struct CursorObject* cursor = (struct CursorObject*)object;
  switch(event->type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
      cursor->sprite[0]->object.flag.render = 0;
      cursor->sprite[2]->object.flag.render = 0;
      cursor->sprite[4]->object.flag.render = 1;
      cursor->sprite[5]->object.flag.render = 1;
      Entity_PushEvent(CURSOR_GRAB, 0, (void*)event->motion.x, (void*)event->motion.y);
      break;
    }
    case SDL_EVENT_MOUSE_BUTTON_UP: {
      cursor->sprite[0]->object.flag.render = 1;
      cursor->sprite[2]->object.flag.render = 1;
      cursor->sprite[4]->object.flag.render = 0;
      cursor->sprite[5]->object.flag.render = 0;
      Entity_PushEvent(CURSOR_DROP, 0, (void*)event->motion.x, (void*)event->motion.y);
      break;
    }
    case SDL_EVENT_MOUSE_MOTION: {
      Cursor_Move(cursor, event->motion.x, event->motion.y);
      Entity_PushEvent(CURSOR_MOVE, 0, (void*)event->motion.x, (void*)event->motion.y);
      break;
    }
    default: {}
  }
}

struct Object* Entity_Create_Cursor() {
  struct CursorObject* cursor = (struct CursorObject*)Object_Create(sizeof(struct CursorObject));
  cursor->object.flag.render = 1;
  cursor->object.onEvent = Cursor_onEvent;

  Transform_LocalTranslate(&cursor->object.transform, 100.0f, 100.0f);

  //create subsprites.
  cursor->sprite[0] = UserSprite_Create(CURSOR1);
  cursor->sprite[1] = UserSprite_Create(CURSOR2);
  cursor->sprite[2] = UserSprite_Create(CURSOR3);
  cursor->sprite[3] = UserSprite_Create(CURSOR4);
  cursor->sprite[4] = UserSprite_Create(CURSOR5);
  cursor->sprite[5] = UserSprite_Create(CURSOR6);

  Object_SetParent((struct Object*)cursor->sprite[0], cursor);
  Object_SetParent((struct Object*)cursor->sprite[1], cursor);
  Object_SetParent((struct Object*)cursor->sprite[2], cursor);
  Object_SetParent((struct Object*)cursor->sprite[3], cursor);
  Object_SetParent((struct Object*)cursor->sprite[4], cursor);
  Object_SetParent((struct Object*)cursor->sprite[5], cursor);

  cursor->sprite[0]->object.flag.render = 1;
  cursor->sprite[1]->object.flag.render = 1;
  cursor->sprite[2]->object.flag.render = 1;
  cursor->sprite[3]->object.flag.render = 1;
  cursor->sprite[4]->object.flag.render = 0;
  cursor->sprite[5]->object.flag.render = 0;

  Transform_LocalTranslate(&(cursor->sprite[0]->object.transform), -16.0f, 0.0f);
  Transform_LocalTranslate(&(cursor->sprite[1]->object.transform), 16.0f, 0.0f);
  Transform_LocalTranslate(&(cursor->sprite[2]->object.transform), -16.0f, 32.0f);
  Transform_LocalTranslate(&(cursor->sprite[3]->object.transform), 16.0f, 32.0f);
  Transform_LocalTranslate(&(cursor->sprite[4]->object.transform), -16.0f, 0.0f);
  Transform_LocalTranslate(&(cursor->sprite[5]->object.transform), -16.0f, 32.0f);

  return cursor;
}
