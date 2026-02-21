#ifndef USERSPRITE_H_
#define USERSPRITE_H_

#include "sprite.h"

enum UserSprite {

  CURSOR1,
  CURSOR2,
  CURSOR3,
  CURSOR4,
  CURSOR5,
  CURSOR6,

  SQUARE,
  GOBLIN,
  MOUNTA,
  FIELDS,

  USERSPRITE_COUNT
};

struct Sprite* UserSprite_Create(int id);

void UserSprite_DebugDraw();

#endif
