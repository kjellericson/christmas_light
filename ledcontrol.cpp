#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "arduino.h"
#include "ledcontrol.h"
FILE *spidev;

struct rgb ledbuffer[MAXLEDS];
struct rgb fadebuffer[MAXLEDS];
double fading = 0;
bool whiteoverlay_enabled = false;
void do_whiteoverlay(struct rgb *leds);

int calc_fade(double fading, int fade1, int fade0)
{
  if (fading <= 0)
    return fade0;
  return (fade1 * fading) + (fade0 * (1-fading)); 
}

void flushbuffer()
{
  int i;
  struct rgb tmpbuffer[MAXLEDS];
  memcpy(tmpbuffer, ledbuffer, sizeof(ledbuffer));

  if (fading <= 0 && whiteoverlay_enabled) {
    do_whiteoverlay(tmpbuffer);
  }

  for (i = 0; i < MAXLEDS; i++) {
    fputc(calc_fade(fading, fadebuffer[i].r, tmpbuffer[i].r), spidev);
    fputc(calc_fade(fading, fadebuffer[i].g, tmpbuffer[i].g), spidev);
    fputc(calc_fade(fading, fadebuffer[i].b, tmpbuffer[i].b), spidev);
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

void fade_out()
{
  fade();
  for (int i = 0; i < MAXLEDS; i++) {
    ledbuffer[i].r = 0;
    ledbuffer[i].g = 0;
    ledbuffer[i].b = 0;
  }

  while (fading >= 0) {
    int nsdelay = 1000000/60;
    flushbuffer();
    usleep(nsdelay);
  }
}

void whiteoverlay(bool on)
{
  whiteoverlay_enabled = on;
}

void do_whiteoverlay(struct rgb *leds)
{
  int lamp_len = 15;
  int offset = ((millis() / 50) % (MAXLEDS*2)) - lamp_len;
  //printf("%d, %lu: ", offset, millis());
  for (int i = 0; i < lamp_len; i++) {
    int led = offset + i;

    if (led >= 0 && led < MAXLEDS) {
      double v = sin((((double)i)/lamp_len)*3.14)*60;
      //printf("(%d, %f)", led, v);
      if (v > 0) {
	leds[led].r = (int)(leds[led].r * (1.0-v) + 255 * v);
	leds[led].g = (int)(leds[led].g * (1.0-v) + 255 * v);
	leds[led].b = (int)(leds[led].b * (1.0-v) + 255 * v);
      }
    }
  }
  //printf("\n");
}
