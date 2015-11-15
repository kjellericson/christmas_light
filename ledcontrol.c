#include <stdlib.h>
#include <stdio.h>
#include "ledcontrol.h"
FILE *spidev;

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

void ledcontrol_init()
{
  spidev = fopen("/dev/spidev0.0", "wb");
  if (!spidev) {
    printf("Couldn't open spidev. Not root?\n");
    exit(0);
  }
}
