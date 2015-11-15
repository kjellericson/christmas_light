#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#define MAXLEDS 100

struct rgb {
  int r, g, b;
};
extern struct rgb buffer[MAXLEDS];

void flushbuffer();
void ledcontrol_init();

#endif
