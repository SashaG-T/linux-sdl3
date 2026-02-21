#include "entity.h"
#include <SDL3/SDL.h>

unsigned int entityBaseEventId;

void Entity_RegisterEvents() {
  entityBaseEventId = SDL_RegisterEvents(ENTITY_EVENT_TYPE_COUNT);
}

int Entity_GetEventType(int eventType) {
  int type = eventType - entityBaseEventId;
  if(type < 0 || type >= ENTITY_EVENT_TYPE_COUNT) {
    type = 0;
  }
  return type;
}

void Entity_PushEvent(enum EntityEventType type, int code, void* data1, void* data2) {
  if(entityBaseEventId != 0) {
    SDL_Event event;
    SDL_zero(event);
    event.type = entityBaseEventId + type;
    event.user.code = code;
    event.user.data1 = data1;
    event.user.data2 = data2;
    int success = SDL_PushEvent(&event);
    PrintError(!success);
  }
}
