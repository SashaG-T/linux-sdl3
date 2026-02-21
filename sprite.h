#ifndef SPRITE_H_
#define SPRITE_H_

#include "object.h"
#include <SDL3/SDL.h>
#include "texture.h"

struct Sprite {
  struct Object object;
  struct Texture* texture;
  int i;
  SDL_FRect src;
  unsigned int dw, dh;
};

struct Sprite* Sprite_Create(struct Texture* texture, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int dw, unsigned int dh);

#endif
