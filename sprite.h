#ifndef SPRITE_H_
#define SPRITE_H_

#include "object.h"
#include <SDL3/SDL.h>

struct Sprite {
  struct Object object;
  SDL_Texture* texture;
  int i;
};

struct Sprite* Sprite_Create(char* filename);

#endif
