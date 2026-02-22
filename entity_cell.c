#include "entity.h"
#include "usersprite.h"
#include "global.h"
#include "collision.h"

void Cell_onEvent() {
  if(!object->flag.render) {
    return;
  }
  struct CellObject* cell = (struct CellObject*)object;
  switch(Entity_GetEventType(event->type)) {
    case CARD_GRAB: {
      if(!cell->card) {
        break;
      }
      struct CardEvent* cardEvent = (struct CardEvent*)event->user.data1;
      struct CardObject* grabbedCard = cardEvent->card;
      if(cell->card == grabbedCard) {
        Entity_Cell_DetachCard(cell);
      }
      break;
    }
    case CARD_DROP: {
      if(cell->card) {
        break;
      }
      struct CardEvent* cardEvent = (struct CardEvent*)event->user.data1;
      struct CardObject* droppedCard = cardEvent->card;
      struct Vector* p = &(droppedCard->grabbable.object.transform.position);
      struct Vector* c = &(cell->object.transform.position);
      if(Collision_PointInAABB(p->x+32, p->y+32, c->x, c->y, 64, 64)) {
        Entity_Cell_AttachCard(cell, droppedCard);
      }
      break;
    }
    case NON_USER_EVENT:
    default: {}
  }
}

struct Object* Entity_Create_Cell(int x, int y) {
  struct CellObject* cell = (struct CellObject*)Object_Create(sizeof(struct CellObject));
  cell->object.flag.render = 1;
  cell->object.onEvent = Cell_onEvent;
  cell->card = 0;
  cell->locking = 0;

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

void Entity_Cell_AttachCard(struct CellObject* cell, struct CardObject* card) {
  struct Vector* c = &(cell->object.transform.position);
  card->grabbable.isGrabbable = !cell->locking;
  cell->card = card;
  Transform_SetPosition(&(card->grabbable.object.transform), c->x, c->y);
  Entity_PushEvent(CELL_CARD_ATTACHED, 0, (void*)cell, (void*)card);
}

void Entity_Cell_DetachCard(struct CellObject* cell) {
  struct CardObject* card = cell->card;
  if(!card) {
    return;
  }
  cell->card = 0;
  card->grabbable.isGrabbable = 1;
  Entity_PushEvent(CELL_CARD_DETACHED, 0, (void*)cell, (void*)card);
}
