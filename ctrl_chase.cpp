#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "ledcontrol.h"

int nsdelay = 1000000/60;

void fillinchase(float ir, int rgb)
{
    int brightness;
    int i;

    int pos = (int)ir;
    brightness = (ir - pos)*32;
    for (i = 0; i < 4; i++) {
      switch (rgb) {
      case 1:
	ledbuffer[pos].r = brightness;
	break;
      case 2:
	ledbuffer[pos].g = brightness;
	break;
      case 0:
	ledbuffer[pos].b = brightness;
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
	ledbuffer[pos].r = brightness;
	break;
      case 2:
	ledbuffer[pos].g = brightness;
	break;
      case 0:
	ledbuffer[pos].b = brightness;
	break;
      }
      pos++;
      if (pos > MAXLEDS)
	pos = 0;
      brightness -= 48;
    }
}


void ctrl_chase()
{
  float ir = 0;
  float ig = 0;
  float igc = 0;
  float ib = 0;
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
