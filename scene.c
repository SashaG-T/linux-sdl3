#include "scene.h"
#include "sprite.h"

#include "time.h"

void Test_Update() {
Transform_Rotate(&object->transform, 360.0f * Time_elapsed.delta);
//Transform_LocalTranslate(&object->transform, 0.01f, 0.005f);
  
}

void Sprite2Update() {
Transform_Rotate(&object->transform, -360.0f * Time_elapsed.delta);
}

struct Object* Scene_CreateTestScene() {
  struct Object* scene = Object_Create(sizeof(struct Object));
  struct Object* girlSprite = (struct Object*)Sprite_Create("girl.png");
  struct Object* girlSprite2 = (struct Object*)Sprite_Create("girl.png");
  scene->update = Test_Update;
  Transform_LocalTranslate(&scene->transform, 100.0f, 100.0f);
  girlSprite2->update = Sprite2Update;
  //Transform_Rotate(&scene->transform, 30.0f);
  Object_SetParent(girlSprite, scene);
  Object_SetParent(girlSprite2, girlSprite);
  Transform_LocalTranslate(&girlSprite2->transform, 0.0f, 100.0f);
  //Transform_Recalculate(&girlSprite2->transform, &girlSprite->transform);
  return scene;
}
