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
    Object_InitRoot();
    Object_SetParent(Scene_CreateTestScene(), 0);

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
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }	
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
/*



    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
    SDL_RenderPresent(renderer);
*/

    Time_Update();

    char message[256] = {0};
    snprintf(message, sizeof(message), "Time: %d", SDL_GetTicks());
    message[255] = 0;
    int w = 0, h = 0;
    float x, y;
    const float scale = 4.0f;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //Handle Objects
    //puts("Handling Objects");
    CallObjectFuncRecursive(rootObjPtr, offsetof(struct Object, update)); //update
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
    CallObjectFuncRecursive(rootObjPtr, offsetof(struct Object, render)); //render
    SDL_RenderPresent(renderer);

    //Destroy Objects
    DestroyFlaggedObjects(rootObjPtr);

    //Add new objects that were created this frame
    Object_AddNewObjects();
    Object_ResolveReparenting();    

    //Make sure transforms are clean
    CleanTransforms(rootObjPtr, 0);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}


