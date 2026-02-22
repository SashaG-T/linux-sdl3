#include "entity.h"
#include "usersprite.h"
#include "global.h"

void Hand_onEvent() {
  struct HandObject* hand = (struct HandObject*)object;
  switch(Entity_GetEventType(event->type)) {
    //we'll be listening for Grabbable events
    case NON_USER_EVENT:
    default: {}
  }
}

struct Object* Entity_Create_Hand(int x, int y) {
  struct HandObject* hand = (struct HandObject*)Object_Create(sizeof(struct HandObject));
  hand->object.onEvent = Hand_onEvent;

  Transform_LocalTranslate(&hand->object.transform, (float)x, (float)y);

  for(int y = 0; y < 3; y++) {
    for(int x = 0; x < 3; x++) {
      int i = x + y * 3;
        struct Obect* cell = Entity_Create_Cell(x * 64, y * 64);
        hand->cell[i] = cell;
        Object_SetParent(cell, hand);
    }
  }

  return (struct Object*)hand;
}

void Entity_Hand_AddCard(struct HandObject* hand, struct CardObject* card){
  int cellId = 0;
  struct CellObject* cell = 0;
  for(; cellId < 9; cellId++) {
    cell = (struct CellObject*)hand->cell[cellId];
    if(!cell->card) {
      break;
    }
  }
  if(cellId >= 9) {
    return;
  }
  Entity_Cell_AttachCard(cell, card);
}

int Entity_Hand_EmptyCellCount(struct HandObject* hand) {
  int count = 0;
  for(int i = 0; i < 9; i++) {
    struct CellObject* cell = (struct CellObject*)hand->cell[i];
    if(!cell->card) {
      count++;
    }
  }
  return count;
}

