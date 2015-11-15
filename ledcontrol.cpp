#include <stdlib.h>
#include <stdio.h>
#include "ledcontrol.h"
FILE *spidev;

struct rgb ledbuffer[MAXLEDS];

void flushbuffer()
{
  int i;
  for (i = 0; i < MAXLEDS; i++) {
    fputc(ledbuffer[i].r, spidev);
    fputc(ledbuffer[i].g, spidev);
    fputc(ledbuffer[i].b, spidev);
  }
  fflush(spidev);
}

void ledcontrol_init()
{
  spidev = fopen("/dev/spidev0.0", "wb");
  if (!spidev) {
    printf("Couldn't open spidev. Not root?\n");
    exit(0);
  }
}
