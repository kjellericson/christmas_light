#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include "ledcontrol.h"

extern void ctrl_chase();
extern void ctrl_icecrystals();

void signal_handler(int s)
{
  printf("Caught signal %d\n",s);
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    ledbuffer[i].r = 0;
    ledbuffer[i].g = 0;
    ledbuffer[i].b = 0;
  }
  flushbuffer();
  usleep(100);
  exit(0);
}


int main()
{
  struct sigaction sigIntHandler;
  
  sigIntHandler.sa_handler = signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  
  sigaction(SIGINT, &sigIntHandler, NULL);

  ledcontrol_init();

  //  ctrl_chase();
  ctrl_icecrystals();
  return 0;
}
