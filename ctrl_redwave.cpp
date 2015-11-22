// From MashedPixels project
// A red wave is progressing along the led strip and the brighter leds
// randomnly flashes white.
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "ledcontrol.h"
#include "arduino.h"

class RedWaveMode
{
  private:
  int count;
  int mode;
  bool change_direction;

  public:
  RedWaveMode(int pCount, int pMode);
  void loop(struct rgb *leds);
  void init();
};

RedWaveMode::RedWaveMode(int pCount, int pMode){
  mode = pMode;
  count = pCount;
}
void RedWaveMode::init()
{
  change_direction = ((millis()/10) & 1) ? true : false;
}

void RedWaveMode::loop(struct rgb *leds){
   struct rgb color;

   int last=-100;
   for(int i = 0; i < count; i++) {
     int led = i;
     if (change_direction)
       led = count - 1 - i;

      // Turn our current led on to white, then show the leds
     double v = sin(i*0.3+millis()/1000.0)*255;
     if (0 && v>240 && random(0,100)>98 && led - last > 10){
       last = led;
       leds[led].g = 250;
       leds[led].r = 255;
       leds[led].b = 252;
       
     } else {
       leds[led].r = mode == 0 ? constrain(v, 0, 255) : 0;
       leds[led].g = mode == 1 ? constrain(v, 0, 255) : 0;
       leds[led].b = mode == 2 ? constrain(v, 0, 255) : 0;
     }
   }
}

void ctrl_redwave(int secs, int mode)
{
  int nsdelay = 1000000/60;
  time_t start = time(NULL);
  time_t now;
  RedWaveMode red(MAXLEDS, mode);
  red.init();

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

