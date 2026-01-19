#include "time.h"
#include <SDL3/SDL.h>

struct Time Time_elapsed;

void Time_Init() {
  Time_elapsed = (struct Time){0, 0.0f};
}

void Time_Update() {
  static unsigned int last = 0;
  static unsigned long ns = 0;

  //about ~49 days 'last' will be larger than 'ticks'..
  //just assume the frame took about the same time as the previous one.
  //(i.e.: Just leave it's values as is)

  unsigned int ticks = SDL_GetTicks();
  if(last < ticks) {
    Time_elapsed.ms = ticks - last;
  }
  last = ticks;

  unsigned long nano = SDL_GetTicksNS();
  if(ns < nano) {
    Time_elapsed.delta = (nano - ns) / 1000000000.0;
  }
  ns = nano;

}
