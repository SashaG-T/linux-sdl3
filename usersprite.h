#ifndef USERSPRITE_H_
#define USERSPRITE_H_

#include "sprite.h"

enum UserSprite {
/*
  SQUARE,
  GOBLIN,
  MOUNTA,
  FIELDS,
*/
  CURSOR1,
  CURSOR2,
  CURSOR3,
  CURSOR4,

  USERSPRITE_COUNT
};

struct Sprite* UserSprite_Create(int id);

void UserSprite_DebugDraw();

#endif
