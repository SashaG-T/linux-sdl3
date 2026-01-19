#ifndef TIME_H_
#define TIME_H_

struct Time {
  unsigned int ms;
  double delta;
};

extern struct Time Time_elapsed;

void Time_Init();
void Time_Update();

#endif
