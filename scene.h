#ifndef SCENE_H_
#define SCENE_H_

#include "object.h"

struct Object* Scene_CreateTestScene();
struct Object* Scene_CreateMainScene();

//struct Object* Scene_GetScene(unsigned int sceneIndex);
//struct Object* Scene_LoadScene(const char* filename);

#include "sprite.h"
#include "texture.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include "time.h"
#include "global.h"

#endif
