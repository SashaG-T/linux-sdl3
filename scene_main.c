#include "scene.h"
#include "sprite.h"
#include "usersprite.h"
#include "texture.h"
#include "entity.h"

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

  struct Object* cursor = Entity_Create_Cursor();
  Object_SetParent(cursor, scene);

  SDL_HideCursor();

  return scene;
}

