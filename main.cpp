#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include "ledcontrol.h"

extern void ctrl_chase(int secs);
extern void ctrl_icecrystals(int secs);
extern void ctrl_traditional(int secs);
extern void ctrl_redwave(int secs);

void clear()
{
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    ledbuffer[i].r = 0;
    ledbuffer[i].g = 0;
    ledbuffer[i].b = 0;
  }
  flushbuffer();
  usleep(200);
}

void signal_handler(int s)
{
  printf("Caught signal %d\n",s);
  clear();
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

  printf("Redwave\n");
  ctrl_redwave(30);

  printf("Chase\n");
  ctrl_chase(10);

  printf("Icecrystals\n");
  ctrl_icecrystals(30);

  printf("Traditional\n");
  ctrl_traditional(30);
  clear();
  return 0;
}
