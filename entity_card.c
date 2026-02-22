#include "entity.h"
#include "usersprite.h"
#include "global.h"

//void Grab_onEvent();

struct CardEvent cardEvent;

void Card_onGrab() {
  cardEvent.card = (struct CardObject*)object;
  Entity_PushEvent(CARD_GRAB, 0, &cardEvent, 0);
}

void Card_onDrop() {
  cardEvent.card = (struct CardObject*)object;
  Entity_PushEvent(CARD_DROP, 0, &cardEvent, 0);
}


void Entity_Card_RemoveFromPlay(struct CardObject* card) {
  card->inPlay = 0;
  Transform_SetPosition(&(card->grabbable.object.transform), -128.0f, -128.0f);
}

struct Object* Entity_Create_Card(enum UserSprite spriteId, int x, int y) {
  struct CardObject* card = (struct CardObject*)Object_Create(sizeof(struct CardObject));
  Entity_Init_Grabbable((struct GrabbableObject*)card, 64, 64);
//  card->grabbabl.onEvent = Card_onEvent;
  card->grabbable.onGrab = Card_onGrab;
  card->grabbable.onDrop = Card_onDrop;
  card->inPlay = 0;

  Transform_LocalTranslate(&card->grabbable.object.transform, (float)x, (float)y);

  //create subsprites.
  for(int y = 0; y < 2; y++) {
    for(int x = 0; x < 2; x++) {
      int i = x + y * 2;
      card->sprite[i] = UserSprite_Create(spriteId + i);
      Object_SetParent((struct Object*)card->sprite[i], (struct Object*)card);
      card->sprite[i]->object.flag.render = 1;
      Transform_LocalTranslate(&(card->sprite[i]->object.transform), x * 32.0f, y * 32.0f);
    }
  }

  return (struct Object*)card;
}
