#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "ledcontrol.h"
FILE *spidev;

struct rgb ledbuffer[MAXLEDS];
struct rgb fadebuffer[MAXLEDS];
double fading = 0;

int calc_fade(double fading, int a, int b)
{
  if (fading <= 0)
    return b;
  return (a * fading) + (b * (1-fading)); 
}

void flushbuffer()
{
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    fputc(calc_fade(fading, fadebuffer[i].r, ledbuffer[i].r), spidev);
    fputc(calc_fade(fading, fadebuffer[i].g, ledbuffer[i].g), spidev);
    fputc(calc_fade(fading, fadebuffer[i].b, ledbuffer[i].b), spidev);
  }
  fflush(spidev);
  if (fading > 0) {
    fading -= 0.01;
  }
}

void ledcontrol_init()
{
  spidev = fopen("/dev/spidev0.0", "wb");
  if (!spidev) {
    printf("Couldn't open spidev. Not root?\n");
    exit(0);
  }
}

void fade()
{
  fading = 1;
  memcpy(fadebuffer, ledbuffer, sizeof(ledbuffer));
}
