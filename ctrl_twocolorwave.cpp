// From MashedPixels project
// A red wave is progressing along the led strip and the brighter leds
// randomnly flashes white.
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "ledcontrol.h"
#include "arduino.h"

class TwoColorWave
{
  private:
  int count;
  bool change_direction;
  struct rgb bg_col;
  struct rgb wave_col;

  public:
  TwoColorWave(int pCount);
  void loop(struct rgb *leds);
  void init(struct rgb background, struct rgb wave);
};

TwoColorWave::TwoColorWave(int pCount){
  count = pCount;
}
void TwoColorWave::init(struct rgb background, struct rgb wave)
{
  bg_col = background;
  wave_col = wave;
  change_direction = ((millis()/10) & 1) ? true : false;
}

void TwoColorWave::loop(struct rgb *leds){
   struct rgb color;

   int last=-100;
   for(int i = 0; i < count; i++) {
     int led = i;
     if (change_direction)
       led = count - 1 - i;

     double v = sin(i*0.3+millis()/1000.0);
     double fade = v;
     if (fade < 0)
       fade = 0;
     leds[led].r = calc_fade(fade, constrain(wave_col.r*v, 0, 255), bg_col.r);
     leds[led].g = calc_fade(fade, constrain(wave_col.g*v, 0, 255), bg_col.g);
     leds[led].b = calc_fade(fade, constrain(wave_col.b*v, 0, 255), bg_col.b);
   }
}

void ctrl_twocolorwave(int secs, struct rgb background, struct rgb wave)
{
  int nsdelay = 2000000/60;
  time_t start = time(NULL);
  time_t now;
  TwoColorWave red(MAXLEDS);
  red.init(background, wave);

  time(&start);
  while (1) {
    red.loop(&ledbuffer[0]);
    flushbuffer();
    now = time(NULL);
    if (start + secs < now)
      break;
    usleep(nsdelay);
  }
}

