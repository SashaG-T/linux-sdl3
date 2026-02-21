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

  //Grabbable
  struct Object* grabbable = Entity_Create_Grabbable(32, 32);
  struct Sprite* goblin = UserSprite_Create(GOBLIN);
  Object_SetParent((struct Object*)goblin, grabbable);
  Object_SetParent(grabbable, scene);

  Transform_SetLocalPosition(&(goblin->object.transform), 0.0f, 0.0f);
  Transform_SetPosition(&(grabbable->transform), 100.0f, 100.0f);

  //Grid
  struct Object* cell1 = Entity_Create_Cell(640, 640);
  struct Object* cell2 = Entity_Create_Cell(704, 640);
  Object_SetParent(cell1, scene);
  Object_SetParent(cell2, scene);

  //Cursor
  struct Object* cursor = Entity_Create_Cursor();
  Object_SetParent(cursor, scene);
  SDL_HideCursor();

  return scene;
}

