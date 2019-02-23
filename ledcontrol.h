#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#define MAXLEDS 100

struct rgb {
  int r, g, b;
};
extern struct rgb ledbuffer[MAXLEDS];

void flushbuffer();
void ledcontrol_init();
void whiteoverlay(bool);

// Mix values. If fade = 1 then more of fade1-color
int calc_fade(double fading, int fade1, int fade0);

void fade();
void fade_out();

#endif
