#include "sprite.h"
#include "png.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
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

void defaultSpriteDestroy() {
    printf("Destroy Sprite: %d\n", object->id);
    struct Sprite* sprite = (struct Sprite*)object;
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = 0;
}

void defaultSpriteUpdate() {
    struct Sprite* sprite = (struct Sprite*)object;
}

void defaultSpriteRender() {
    if(!object->flag.render) {
        return;
    }
    struct Sprite* sprite = (struct Sprite*)object;
    struct Vector position;
    float rotation;
    Transform_GetPosition(&object->transform, &position);
    Transform_GetRotation(&object->transform, &rotation);
    SDL_FPoint centre = {50.0f, 50.0f};
    SDL_FRect dest = {position.x-centre.x, position.y-centre.y, 100.0f, 100.0f};
    SDL_RenderTextureRotated(renderer, sprite->texture, NULL, &dest, (double)rotation, &centre, SDL_FLIP_NONE);
}

struct Sprite* Sprite_Create(char* filename) {
    struct Sprite* spritePtr = (struct Sprite*)Object_Create(sizeof(struct Sprite));
    spritePtr->object.update = defaultSpriteUpdate;
    spritePtr->object.destroy = defaultSpriteDestroy;
    spritePtr->object.render = defaultSpriteRender;
    spritePtr->object.flag.render = 1;
    unsigned char *pixels;
    unsigned width, height;
    if(load_png_rgba(filename, &pixels, &width, &height)) {
        SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, pixels, width * 4);
        if(!surface) {
            printf("Failed to load '%s': Failed to create Surface.\n", filename);
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(!texture) {
            printf("Failed to load '%s': Failed to create Texture (Renderer: %X, Surface: %X)\n", filename, renderer, surface);
        }
        spritePtr->texture = texture;
	SDL_DestroySurface(surface);
        free(pixels);	
    } else {
        printf("Failed to load '%s': load_png_rgba failure.\n", filename);
    }
    return spritePtr;
}
