#include "entity.h"
#include "usersprite.h"
#include "global.h"

struct CellObject {
  struct Object object;
  struct Sprite* sprite[4];
};

void Cell_onEvent() {
  struct CellObject* cell = (struct CellObject*)object;
  switch(Entity_GetEventType(event->type)) {
    //we'll be listening for Grabbable events
    case NON_USER_EVENT:
    default: {}
  }
}

struct Object* Entity_Create_Cell(int x, int y) {
  struct CellObject* cell = (struct CellObject*)Object_Create(sizeof(struct CellObject));
  cell->object.flag.render = 1;
  cell->object.onEvent = Cell_onEvent;

  Transform_LocalTranslate(&cell->object.transform, (float)x, (float)y);

  //create subsprites.
  cell->sprite[0] = UserSprite_Create(SQUARE1);
  cell->sprite[1] = UserSprite_Create(SQUARE2);
  cell->sprite[2] = UserSprite_Create(SQUARE3);
  cell->sprite[3] = UserSprite_Create(SQUARE4);

  Object_SetParent((struct Object*)cell->sprite[0], (struct Object*)cell);
  Object_SetParent((struct Object*)cell->sprite[1], (struct Object*)cell);
  Object_SetParent((struct Object*)cell->sprite[2], (struct Object*)cell);
  Object_SetParent((struct Object*)cell->sprite[3], (struct Object*)cell);

  cell->sprite[0]->object.flag.render = 1;
  cell->sprite[1]->object.flag.render = 1;
  cell->sprite[2]->object.flag.render = 1;
  cell->sprite[3]->object.flag.render = 1;

  Transform_LocalTranslate(&(cell->sprite[0]->object.transform), 0.0f, 0.0f);
  Transform_LocalTranslate(&(cell->sprite[1]->object.transform), 32.0f, 0.0f);
  Transform_LocalTranslate(&(cell->sprite[2]->object.transform), 0.0f, 32.0f);
  Transform_LocalTranslate(&(cell->sprite[3]->object.transform), 32.0f, 32.0f);

  return (struct Object*)cell;
}