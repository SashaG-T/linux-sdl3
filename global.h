#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <SDL3/SDL.h>
#include <stdio.h>

#define PrintError(cond) if((cond)) { printf("Error: %s:%d: %s\n", __FILE__, __LINE__, SDL_GetError()); }

extern SDL_Renderer* renderer;

#endif
