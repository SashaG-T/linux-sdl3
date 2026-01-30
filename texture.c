#include "texture.h"
#include "array.h"
#include "png.h"
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

int load_png_rgba(const char* filename, unsigned char** pixels, unsigned* width, unsigned* height) {

  FILE*fp = fopen(filename, "rb");
  if(!fp) {
    return 0;
  }

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) {
    return 0;
  }

  png_infop info = png_create_info_struct(png);
  if(!info) {
    return 0;
  }

  if(setjmp(png_jmpbuf(png))) {
    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);
    return 0;
  }

  png_init_io(png, fp);
  png_read_info(png, info);

  int w = png_get_image_width(png, info);
  int h = png_get_image_height(png, info);
  png_byte colour_type = png_get_color_type(png, info);
  png_byte bit_depth = png_get_bit_depth(png, info);

  if(bit_depth == 16) {
    png_set_strip_16(png);
  }

  if(colour_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png);
  }

  if(colour_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
    png_set_expand_gray_1_2_4_to_8(png);
  }

  if(png_get_valid(png, info, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png);
  }

  if(colour_type == PNG_COLOR_TYPE_RGB ||
     colour_type == PNG_COLOR_TYPE_GRAY ||
     colour_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
  }

  png_read_update_info(png, info);

  unsigned char* p = malloc(w * h * 4);
  png_bytep* rows = malloc(sizeof(png_bytep) * h);

  for(int y = 0; y < h; y++) {
    rows[y] = p + y * w * 4;
  }

  png_read_image(png, rows);
  free(rows);

  png_destroy_read_struct(&png, &info, NULL);
  fclose(fp);

  *pixels = p;
  *width = w;
  *height = h;
  return 1;
}

typedef struct Texture Tex;
ARRAY_DECL(Tex)
Array_Tex_t textureArray;

void Texture_Init() {
  Array_Init(textureArray, Tex, 0);
}

void Texture_Cleanup() {
  for(struct Texture* texture = textureArray.start; texture < textureArray.end; texture++) {
    if(texture->destroy) {
      texture->destroy(texture);
    }
  }
  Array_Destroy(textureArray);
}

void Texture_DefaultDestroy(struct Texture* texture) {
  SDL_DestroyTexture(texture->texture);
}

void Texture_DefaultReload(struct Texture* texture) {
  unsigned char *pixels;
  unsigned width, height;
  const char* filename = texture->userdata;
  if(load_png_rgba(filename, &pixels, &width, &height)) {
    SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, pixels, width * 4);
    if(!surface) {
       printf("Failed to load '%s': Failed to create Surface.\n", filename);
    }
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!newTexture) {
      printf("Failed to load '%s': Failed to create Texture (Renderer: %X, Surface: %X)\n", filename, renderer, surface);
    }
      texture->texture = newTexture;
      SDL_DestroySurface(surface);
      free(pixels);	
  } else {
    printf("Failed to load '%s': load_png_rgba failure.\n", filename);
  }
}

struct Texture* Texture_LoadPNG(const char* filename) {

  #warning TODO: If filename is already loaded then just return that one and increment its refCount.

  struct Texture* texture = Array_Expand(textureArray);
  texture->userdata = (void*)filename;
  texture->texture = 0;
  texture->reload = Texture_DefaultReload;
  texture->destroy = Texture_DefaultDestroy;
  texture->refCount = 1;
  Texture_DefaultReload(texture);
  return texture;
}
