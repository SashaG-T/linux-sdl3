#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL3/SDL.h>

struct Texture {
  SDL_Texture* texture;
  int refCount;
  void* userdata;
  void (*reload)(struct Texture* texture); //should be onDeviceReset, onTargetReset, and onWindowResize/PixelSizeChanged callbacks independently
#warning See note above this line.
  void (*destroy)(struct Texture* texture);
};

struct Texture* Texture_LoadPNG(const char* filename);
struct Texture* Texture_Generate(void* userdata, void (*reload)(struct Texture* texture), void (*destroy)(struct Texture* texture));
void Texture_Reference(struct Texture* texture);
void Texture_Dereference(struct Texture* texture);

void Texture_Init();
void Texture_Cleanup();

#endif
