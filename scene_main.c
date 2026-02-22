#include "scene.h"
#include "sprite.h"
#include "usersprite.h"
#include "texture.h"
#include "entity.h"

#include <stdio.h>
#include <SDL3/SDL.h>

#include "time.h"
#include "global.h"

#include <stdlib.h>

struct CardObject* deck[256];
unsigned int nextCard = 0;

struct Object* grid = 0;
struct Object* hand = 0;

enum GameState {
  INIT_STATE,
  DRAW_STATE,
  BUILD_STATE,
  DROP_STATE,
  GAME_STATE_COUNT
};

enum GameState currState = INIT_STATE;

enum UserSprite RandomCard() {
  return CARD_BLANK + (random() % ((USERSPRITE_COUNT - CARD_BLANK)/4)) * 4;
}

void Main_Init_Deck(struct Object* scene) {

  srandom(SDL_GetTicks());
 
  for(int i = 0; i < 256; i++) {
    struct CardObject* card = Entity_Create_Card(RandomCard(), -128, -128);
    deck[i] = card;
//    Transform_SetLocalPosition(&(card->grabbable.object.transform.position), -128.0f, -128.0f);
    Object_SetParent(card, scene);
  }
}

struct CardObject* Main_DrawCard() {
  struct CardObject* card = 0;
  for(int i = 0; i < 256; i++) {
    int cardId = (i + nextCard) % 256;
    struct CardObject* c = deck[i];
    if(!c->inPlay) {
      nextCard = cardId + 1;
      card = c;
      break;
    }
  }
  card->inPlay = 1;
  return card;  
}

void Main_Update() {

}

void Main_DrawCards() {
  puts("drawing");
  int drawCount = Entity_Hand_EmptyCellCount(hand);
  printf("drawCount: %d\n", drawCount);
  for(int i = 0; i < drawCount; i++) {
    struct CardObject* card = Main_DrawCard();
    if(!card) {
      break;
    }
    Entity_Hand_AddCard(hand, card);
  }
}

void Main_SetState(enum GameState state) {
  enum GameState lastState = currState;
  currState = state;
  switch(state) {
    case INIT_STATE: {
      break;
    }
    case DRAW_STATE: {
      Main_DrawCards();
      break;
    }
    case BUILD_STATE: {
      break;
    }
    case DROP_STATE: {
      break;
    }
    default: {}
  }
}

void Main_onEvent() {
  switch(Entity_GetEventType(event->type)) {
    case BUILD_COMPLETE: {
      Main_DrawCards();
      break;
    }
    default: {}
  }
}

struct Object* Scene_CreateMainScene() {
  struct Object* scene = Object_Create(sizeof(struct Object));
  scene->update = Main_Update;
  scene->onEvent = Main_onEvent;
  scene->flag.render = 1;

  //Grid
  grid = Entity_Create_Grid(512, 64);
  Object_SetParent(grid, scene);

  //Grid
  hand = Entity_Create_Hand(64, 64);
  Object_SetParent(hand, scene);

  //Card (For testing)
  //struct Object* card = Entity_Create_Card(CARD_BLANK, 640, 256);
  //Object_SetParent(card, scene);

  //Deck (Cards)
  Main_Init_Deck(scene);

  //Grabbable (Just for funsies!)
  struct Object* grabbable = Entity_Create_Grabbable(32, 32);
  struct Sprite* goblin = UserSprite_Create(GOBLIN);
  Object_SetParent((struct Object*)goblin, grabbable);
  Object_SetParent(grabbable, scene);
  Transform_SetLocalPosition(&(goblin->object.transform), 0.0f, 0.0f);
  Transform_SetPosition(&(grabbable->transform), 512.0f, 128.0f);

  //Cursor
  struct Object* cursor = Entity_Create_Cursor();
  Object_SetParent(cursor, scene);
  SDL_HideCursor();

  Main_SetState(DRAW_STATE);

  return scene;
}

