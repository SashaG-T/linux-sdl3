#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include "global.h"

void defaultSpriteDestroy() {
    printf("Destroy Sprite: %d\n", object->id);
    struct Sprite* sprite = (struct Sprite*)object;
    sprite->texture->refCount--;
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
    SDL_FRect dest = {position.x-centre.x, position.y-centre.y, sprite->dw, sprite->dh};
    SDL_RenderTextureRotated(renderer, sprite->texture->texture, &sprite->src, &dest, (double)rotation, &centre, SDL_FLIP_NONE);
}

struct Sprite* Sprite_Create(struct Texture* texture, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int dw, unsigned int dh) {
    struct Sprite* spritePtr = (struct Sprite*)Object_Create(sizeof(struct Sprite));
    spritePtr->object.update = defaultSpriteUpdate;
    spritePtr->object.destroy = defaultSpriteDestroy;
    spritePtr->object.render = defaultSpriteRender;
    spritePtr->object.flag.render = 1;
    spritePtr->texture = texture;
    spritePtr->src = (SDL_FRect){(float)x, (float)y, (float)w, (float)h};
    spritePtr->dw = dw;
    spritePtr->dh = dh;
    texture->refCount++;
    return spritePtr;
}
