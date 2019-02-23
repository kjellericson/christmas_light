// From MashedPixels project
// Emulates traditionnal chrismas lights each led has a predefined color (Red, green, blue, yellow) and blinks all at the same time.

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "ledcontrol.h"

class TraditionalMode{
  private:
    int count;
    int move;
    int domove;
    
  public:
    TraditionalMode(int pCount);
    void loop(struct rgb *leds);
    void init();
};


TraditionalMode::TraditionalMode(int pCount){
  count = pCount;
  move = 0;
  domove = 0;
}
void TraditionalMode::init(){

}

int moveTo(int now, int want)
{
  if (now < want)
    now++;
  if (now > want)
    now--;
  return now;
}

void TraditionalMode::loop(struct rgb *leds){
   int colors[] = {
                              255,0,0,
                              0,180,0,
                              0,0,150,
                              180,150,0
                            };
  for (int a=0;a<count;a++){
    int step = (a + move)%4;
    if((time(NULL)%4)==0){
      leds[a].r = moveTo(leds[a].r, colors[step*3]);
      leds[a].g = moveTo(leds[a].g, colors[step*3+1]);
      leds[a].b = moveTo(leds[a].b, colors[step*3+2]);
      domove = 0;
    } else {
      leds[a].r = moveTo(leds[a].r, colors[step*3]/20);
      leds[a].g = moveTo(leds[a].g, colors[step*3+1]/20);
      leds[a].b = moveTo(leds[a].b, colors[step*3+2]/20);
      if (domove == 0)
        domove = 1;
    }
  }
  if (domove == 1) {
    move++;
    domove = 2;
  }
}

void ctrl_traditional(int secs)
{
  TraditionalMode tm(MAXLEDS);
  int nsdelay = 2000000/60;

  time_t start = time(NULL);
  time_t now;

  tm.init();

  time(&start);
  while (1) {
    tm.loop(&ledbuffer[0]);
    flushbuffer();
    now = time(NULL);
    if (start + secs < now)
      break;
    usleep(nsdelay);
  }
}
