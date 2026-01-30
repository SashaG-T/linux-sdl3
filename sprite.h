#ifndef SPRITE_H_
#define SPRITE_H_

#include "object.h"
#include <SDL3/SDL.h>
#include "texture.h"

struct Sprite {
  struct Object object;
  struct Texture* texture;
  int i;
};

struct Sprite* Sprite_Create(struct Texture* texture);

#endif
