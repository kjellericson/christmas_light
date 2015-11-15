#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>

FILE *spidev;
int nsdelay = 1000000/60;
#define MAXLEDS 100

struct rgb {
  int r, g, b;
};
struct rgb buffer[MAXLEDS];


void flushbuffer()
{
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    fputc(buffer[i].r, spidev);
    fputc(buffer[i].g, spidev);
    fputc(buffer[i].b, spidev);
  }
  fflush(spidev);
}

void my_handler(int s)
{
  printf("Caught signal %d\n",s);
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    buffer[i].r = 0;
    buffer[i].g = 0;
    buffer[i].b = 0;
  }
  flushbuffer();
  usleep(100);
  exit(0);
}


#if 1
void fillinchase(float ir, int rgb)
{
    int brightness;
    int i;

    int pos = (int)ir;
    brightness = (ir - pos)*32;
    for (i = 0; i < 4; i++) {
      switch (rgb) {
      case 1:
	buffer[pos].r = brightness;
	break;
      case 2:
	buffer[pos].g = brightness;
	break;
      case 0:
	buffer[pos].b = brightness;
	break;
      }
      pos++;
      if (pos > MAXLEDS)
	pos = 0;
      brightness += 48;
    }
    for (i = 0; i < 5; i++) {
      switch (rgb) {
      case 1:
	buffer[pos].r = brightness;
	break;
      case 2:
	buffer[pos].g = brightness;
	break;
      case 0:
	buffer[pos].b = brightness;
	break;
      }
      pos++;
      if (pos > MAXLEDS)
	pos = 0;
      brightness -= 48;
    }
}

void chase()
{
  float ir = 0;
  float ig = 0;
  float igc = 0;
  float ib = 0;

  struct sigaction sigIntHandler;
  
  sigIntHandler.sa_handler = my_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  
  sigaction(SIGINT, &sigIntHandler, NULL);


  printf("Chase start\n");

  while (1) {
    fillinchase(ir, 0);
    fillinchase(ig, 1);
    fillinchase(ib, 2);
    flushbuffer();

    ir += .1;
    igc += .01;
    ig = sin(igc) * (MAXLEDS/2) + MAXLEDS/2;
    ib -= .1;
    if (ir > MAXLEDS)
      ir -= MAXLEDS;
    if (ig > MAXLEDS)
      ig -= MAXLEDS;
    if (ib > MAXLEDS)
      ib -= MAXLEDS;
    if (ib < 0)
      ib += MAXLEDS;
    usleep(nsdelay);
  }
}
#endif

int main()
{
  spidev = fopen("/dev/spidev0.0", "wb");
  if (!spidev) {
    printf("Couldn't open spidev. Not root?\n");
    exit(0);
  }
  chase();
  printf("Exit\n");
  return 0;
}
