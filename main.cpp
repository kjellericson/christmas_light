41;312;0c#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include "ledcontrol.h"

extern void ctrl_chase(int secs);
extern void ctrl_icecrystals(int secs);
extern void ctrl_traditional(int secs);
extern void ctrl_redwave(int secs, int mode);
extern void ctrl_twocolorwave(int secs, struct rgb background, struct rgb wave);

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
  fade();

  printf("Two color wave\n");
  {
    struct rgb bg = {0,64,0};
    struct rgb fg = {255,0,0};
    ctrl_twocolorwave(25, bg, fg);
    fade();
  }
  
  printf("Redwave\n");
  ctrl_redwave(25, 0);
  fade();
  
  printf("Traditional\n");
  ctrl_traditional(30);
  fade();

  printf("Greenwave\n");
  ctrl_redwave(25, 1);
  fade();

  printf("Two color wave\n");
  {
    struct rgb bg = {128,0,0};
    struct rgb fg = {0,0,255};
    ctrl_twocolorwave(25, bg, fg);
    fade();
  }
  
  printf("Chase\n");
  ctrl_chase(10);
  fade();

  printf("Bluewave\n");
  ctrl_redwave(25, 2);
  fade();

  //  printf("Icecrystals\n");
  // ctrl_icecrystals(30);

  fade_out();
  clear();

  return 0;
}
