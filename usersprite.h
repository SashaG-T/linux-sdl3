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

  SQUARE1,
  SQUARE2,
  SQUARE3,
  SQUARE4,
  TREE,
  MOUNTA,
  GOBLIN,

  CARD_BLANK,
  CARD_BLANK_2,
  CARD_BLANK_3,
  CARD_BLANK_4,

  CARD_HOUSE,
  CARD_HOUSE_2,
  CARD_HOUSE_3,
  CARD_HOUSE_4,

  CARD_FIELD,
  CARD_FIELD_2,
  CARD_FIELD_3,
  CARD_FIELD_4,

  USERSPRITE_COUNT
};

struct Sprite* UserSprite_Create(int id);

void UserSprite_DebugDraw();

#endif
