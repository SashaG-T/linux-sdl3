#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stddef.h>
#include <stdio.h>

#include "list.h"
#include "object.h"
#include "sprite.h"
#include "scene.h"
#include "time.h"
#include "texture.h"

#include "unittest.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void CallObjectFunc(struct Object* objectPtr, size_t funcOffset) {
    void (*func)() = *(void (**)())(((char*)objectPtr)+funcOffset); //this is some f'd up shi
    if(func) {
        func();
    }
}

void CallObjectFuncRecursive(struct Object* objectPtr, size_t funcOffset) {
    if(objectPtr == 0) {
        return;
    }
    //call on self
    object = objectPtr;
    CallObjectFunc(objectPtr, funcOffset);
    //call on children
    struct Object* currObjPtr = 0;
    while(currObjPtr = (struct Object*)List_GetNext(&objectPtr->childList, (struct LNode*)currObjPtr)) {
        CallObjectFuncRecursive(currObjPtr, funcOffset);
    }
}

void DestroyObjectTree(struct Object* objectPtr) {
    if(objectPtr == 0) {
        return;
    }
    struct Object* currObjPtr = 0;
    while(currObjPtr = (struct Object*)List_GetNext(&objectPtr->childList, (struct LNode*)currObjPtr)) {
        DestroyObjectTree(currObjPtr);
        Object_Destroy(currObjPtr);
    }
}

void DestroyFlaggedObjects(struct Object* objectPtr) {
    if(objectPtr == 0) {
        return;
    }
    struct Object* currObjPtr = 0;
    while(currObjPtr = (struct Object*)List_GetNext(&objectPtr->childList, (struct LNode*)currObjPtr)) {
        if(currObjPtr->flag.destroy) {
	    puts("Destroying an Object.");
            struct Object* destroyingObject = currObjPtr;
            currObjPtr = 0;
            List_Remove(&objectPtr->childList, (struct LNode*)destroyingObject);
            DestroyObjectTree(destroyingObject);
        } else {
            DestroyFlaggedObjects(currObjPtr);
        }
    }
}

void CleanTransforms(struct Object* objectPtr, struct Object* parent) {
  if(objectPtr == 0) {
    return;
  }
  struct Object* currObjPtr = 0;
  while(currObjPtr = (struct Object*)List_GetNext(&objectPtr->childList, (struct LNode*)currObjPtr)) {
    if(parent || currObjPtr->transform.dirty) {
      struct Object* p = parent ? parent : objectPtr;
      Transform_Recalculate(&currObjPtr->transform, &p->transform);
      CleanTransforms(currObjPtr, currObjPtr);
    } else {
      CleanTransforms(currObjPtr, 0);
    }
  }
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    UnitTest_RunAllTests();

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Time_Init();
    Texture_Init();
    Entity_RegisterEvents();
    Object_InitRoot();
    Object_SetParent(Scene_CreateMainScene(), 0);

/*
    int i;
    for(i = 0; i < 3; i++) {
        List_Append(&rootObjPtr->childList, (struct LNode*)Object_Create(sizeof(struct Object)));
    }
*/

/*
    for(i = 0; i < 5; i++) {
        List_Append(&((struct Object*)(rootObjPtr->childList.head))->childList, (struct LNode*)Object_Create(sizeof(struct Object)));
    }

    for(i = 0; i < 2; i++) {
        List_Append(&((struct Object*)(rootObjPtr->childList.tail))->childList, (struct LNode*)Object_Create(sizeof(struct Object)));
    }
*/

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *sdlevent)
{
    if (sdlevent->type == SDL_EVENT_KEY_DOWN ||
        sdlevent->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    } else {
        event = sdlevent;
        CallObjectFuncRecursive(rootObjPtr, offsetof(struct Object, onEvent)); //onEvent
    }

    #warning On video context change reload all textures
    //SDL_EVENT_RENDER_DEVICE_RESET
    //  - Destroy SDL_Renderer, SDL_Textures & Regen\load textures
    //SDL_EVENT_RENDER_TARGETS_RESET
    //  - Must redraw textures created using SDL_TEXTUREACCESS_TARGET (no need to destroy them... just redraw)
    //SDL_EVENT_WINDOW_RESIZED / SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED
    //  - Typically fine.. but if images rely on size then regen them.
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    Time_Update();

    //Handle Objects
    SDL_RenderClear(renderer);
    //UserSprite_DebugDraw();
    CallObjectFuncRecursive(rootObjPtr, offsetof(struct Object, update)); //update
    CallObjectFuncRecursive(rootObjPtr, offsetof(struct Object, render)); //render
    //UserSprite_DebugDraw();
    SDL_RenderPresent(renderer);

    //Destroy Objects
    DestroyFlaggedObjects(rootObjPtr);

    //Add new objects that were created this frame
    Object_AddNewObjects();
    Object_ResolveReparenting();    

    //Make sure transforms are clean
    CleanTransforms(rootObjPtr, 0);

    #warning TODO: Destroy textures with refCount 0.

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    Texture_Cleanup();
}


