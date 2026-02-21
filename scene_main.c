#include "scene.h"
#include "sprite.h"
#include "usersprite.h"
#include "texture.h"

#include <stdio.h>
#include <SDL3/SDL.h>

#include "time.h"
#include "global.h"

void Main_Update() {
}

struct Object* Scene_CreateMainScene() {
  struct Object* scene = Object_Create(sizeof(struct Object));
  scene->update = Main_Update;
  scene->flag.render = 1;

  struct Sprite* cursorSprite = UserSprite_Create(CURSOR1);
  Transform_LocalTranslate(&cursorSprite->object.transform, 100.0f, 100.0f);

  Object_SetParent((struct Object*)cursorSprite, scene);

  return scene;
}

