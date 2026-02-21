#include "scene.h"
#include "sprite.h"
#include "texture.h"

#include <stdio.h>
#include <SDL3/SDL.h>

#include "time.h"
#include "global.h"

void Test_Update() {
  Transform_Rotate(&object->transform, 10.0f * Time_elapsed.delta);
  //Transform_Translate(&object->transform, 0.01f, 0.005f);

  struct Vector position;
  Transform_GetPosition(&object->transform, &position);

}

void Sprite2Update() {
  //Transform_Rotate(&object->transform, -360.0f * Time_elapsed.delta);
  Transform_Translate(&object->transform, (100.0f * Time_elapsed.delta), 0.0f);
}

void UpdateText() {
  struct Vector position;
  Transform_GetPosition(&object->transform, &position);
  int secret = object->secret;
  if(position.x > 390) {
    secret = secret | 0x01;
  } else if(position.x < 0) {
    secret = ~(~secret | 0x01);
  }
  if(position.y > 300) {
    secret = secret | 0x02;
  } else if(position.y < 0) {
    secret = ~(~secret | 0x02);
  }

  object->secret = secret;
  position.x = secret & 0x01 ? -1.0f : 1.0f;
  position.y = secret & 0x02 ? -1.0f : 1.0f;

  Vector_Scale(&position, 50.0f * Time_elapsed.delta, &position);
  Transform_Translate(&object->transform, position.x, position.y);
}

void RenderText() {
    char message[256] = {0};
    snprintf(message, sizeof(message), "Time: %d", SDL_GetTicks());
    message[255] = 0;
    int w = 0, h = 0;
    struct Vector position;
    Transform_GetPosition(&object->transform, &position);
    const float scale = 4.0f;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    position.x -= (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    position.y -= (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;
    unsigned char a, r, g, b;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, position.x, position.y, message);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

struct Object* Scene_CreateTestScene() {
  struct Texture* girlTexture = Texture_LoadPNG("girl.png");
  struct Object* scene = Object_Create(sizeof(struct Object));
  struct Object* girlSprite = (struct Object*)Sprite_Create(girlTexture, 0, 0, 644, 910, 64, 91);
  struct Object* girlSprite2 = (struct Object*)Sprite_Create(girlTexture, 0, 0, 644, 910, 64, 91);
  scene->update = Test_Update;
  Transform_LocalTranslate(&scene->transform, 100.0f, 100.0f);
  girlSprite2->update = UpdateText;
  Object_SetParent(girlSprite, scene);
  Object_SetParent(girlSprite2, girlSprite);
  Transform_LocalTranslate(&girlSprite2->transform, 10.0f, 100.0f);
  //Transform_Recalculate(&girlSprite2->transform, &girlSprite->transform);

  //Hello World
  struct Object* hello = Object_Create(sizeof(struct Object));
  hello->update = UpdateText;
  hello->render = RenderText;
  hello->flag.render = 1;
  Object_SetParent(hello, scene);

  return scene;
}

