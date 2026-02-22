#include "entity.h"
#include "usersprite.h"
#include "global.h"

void Grid_ShowAdjacent(struct GridObject* grid, int cellId) {

  int u, d, l, r;

  u = cellId - 7;
  d = cellId + 7;
  l = cellId - 1;
  r = cellId + 1;

  grid->cell[u]->flag.active = 1;
  grid->cell[d]->flag.active = 1;
  grid->cell[l]->flag.active = 1;
  grid->cell[r]->flag.active = 1;

}

void Grid_HandleCardAttachedEvent(struct CellObject* cell, struct CardObject* card) {
  struct GridObject* grid = (struct GridObject*)object;

  int cellId = -1;
  for(int i = 0; i < 49; i++) {
    struct CellObject* c = grid->cell[i];
    if(c == cell) {
      cellId = i;
      goto HandleCardAttachedEvent_OKAY;
    }
  }
  return;

HandleCardAttachedEvent_OKAY:
  
  grid->moveCount++;
  Grid_ShowAdjacent(grid, cellId);
  
}

void Grid_onEvent() {
  struct GridObject* grid = (struct GridObject*)object;
  switch(Entity_GetEventType(event->type)) {
    case CELL_CARD_ATTACHED: {
      if(grid->moveCount < 3) {
        Grid_HandleCardAttachedEvent(event->user.data1, event->user.data2);
      } else {
        grid->moveCount = 0;
        Entity_Grid_Reset(grid);
        Entity_PushEvent(BUILD_COMPLETE, 0, 0, 0);
      }
      break;
    }
    case CELL_CARD_DETACHED: {
      break;
    }
    case NON_USER_EVENT:
    default: {}
  }
}

struct Object* Entity_Create_Grid(int x, int y) {
  struct GridObject* grid = (struct GridObject*)Object_Create(sizeof(struct GridObject));
  grid->object.onEvent = Grid_onEvent;
  grid->moveCount = 0;

  Transform_LocalTranslate(&grid->object.transform, (float)x, (float)y);

/*
x0  x1  x2  .3  x4  x5  x6
x7  x8  .9  .10 .11 x12 x13
x14 .15 .16 .17 .18 .19 x20
.21 .22 .23 .24 .25 .26 .27
x28 .29 .30 .31 .32 .33 x34
x35 x36 .37 .38 .39 x40 x41
x42 x43 x44 .45 x46 x47 x48
*/

  char enabled[49] = {
    0, 0, 0, 1, 0, 0, 0,
    0, 0, 1, 1, 1, 0, 0,
    0, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0,
  };


  for(int y = 0; y < 7; y++) {
    for(int x = 0; x < 7; x++) {
      int i = x + y * 7;
      if(enabled[i]) {
        struct Object* cell = Entity_Create_Cell(x * 64, y * 64);
        ((struct CellObject*)cell)->locking = 1;
        grid->cell[i] = cell;
        Object_SetActive(cell, 0);
        Object_SetParent(cell, grid);
      } else {
        grid->cell[i] = 0;
      }
    }
  }
  Object_SetActive(grid->cell[24], 1);

  return (struct Object*)grid;
}

void Entity_Grid_Reset(struct GridObject* grid) {

  for(int i = 0; i < 49; i++) {
    struct CellObject* cell = grid->cell[i];
    if(!cell) {
      continue;
    }
    Object_SetActive(cell, 0);
    if(cell->card) {
      struct CardObject* card = (struct CardObject*)cell->card;
      Entity_Cell_DetachCard(cell);
      Entity_Card_RemoveFromPlay(card);
    }
  }
  Object_SetActive(grid->cell[24], 1);

}
