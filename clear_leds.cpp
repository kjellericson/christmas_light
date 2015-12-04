#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "ledcontrol.h"

void clear()
{
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    ledbuffer[i].r = 0;
    ledbuffer[i].g = 0;
    ledbuffer[i].b = 0;
  }
  flushbuffer();
  usleep(800);
}

int main()
{
  ledcontrol_init();
  clear();

  return 0;
}
