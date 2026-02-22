#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "object.h"
#include "usersprite.h"

enum EntityEventType {
  NON_USER_EVENT,
  CURSOR_GRAB,
  CURSOR_MOVE,
  CURSOR_DROP,
  CARD_GRAB,
  CARD_DROP,
  CELL_CARD_ATTACHED,
  CELL_CARD_DETACHED,
  BUILD_COMPLETE,
  ENTITY_EVENT_TYPE_COUNT
};

struct GrabbableObject {
  struct Object object;
  int isGrabbable;
  int grabbed;
  int width, height;
  void (*onGrab)();
  void (*onDrop)();
};

struct CellObject {
  struct Object object;
  struct Sprite* sprite[4];
  struct CardObject* card;
  int locking;
};

struct CardObject {
  struct GrabbableObject grabbable;
  struct Sprite* sprite[4];
  int inPlay;
};

struct CursorObject {
  struct Object object;
  struct Sprite* sprite[6];
};

struct GridObject {
  struct Object object;
  struct Object* cell[49];
  unsigned int moveCount;
};

struct HandObject {
  struct Object object;
  struct Object* cell[9];
};

struct CardEvent {
  struct CardObject* card;
};

struct Object* Entity_Create_Cursor();
struct Object* Entity_Create_Grabbable(unsigned int width, unsigned int height);
void Entity_Init_Grabbable(struct GrabbableObject* grabbable, unsigned int width, unsigned int height);
struct Object* Entity_Create_Cell(int x, int y);
struct Object* Entity_Create_Grid(int x, int y);
struct Object* Entity_Create_Hand(int x, int y);
struct Object* Entity_Create_Card(enum UserSprite spriteId, int x, int y);
void Entity_Cell_AttachCard(struct CellObject* cell, struct CardObject* card);
void Entity_Hand_AddCard(struct HandObject* hand, struct CardObject* card);
int Entity_Hand_EmptyCellCount(struct HandObject* hand);
void Entity_Card_RemoveFromPlay(struct CardObject* card);

void Entity_Grid_Reset(struct GridObject* grid);

void Entity_RegisterEvents();
int Entity_GetEventType(int eventType);
void Entity_PushEvent(enum EntityEventType type, int code, void* data1, void* data2);

#endif
