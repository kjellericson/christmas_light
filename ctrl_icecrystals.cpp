#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include "ledcontrol.h"

#define ICE_COUNT 10

enum ice_state {
  ICE_GROWING,
  ICE_FLICKERING,
  ICE_EXPLODING, 
  ICE_SLEEPING
};

long millis()
{
  struct timeval ts;
  gettimeofday(&ts, NULL);
  long ms = ts.tv_sec*1000 + ts.tv_usec;
  return ms;
}

int constrain(int val, int min, int max)
{
  if (val < min)
    return min;
  if (val > max)
    return max;
  return val;
}

struct ice_data{
  double position;
  unsigned long start;
  unsigned long growingSpeed;
  unsigned long flickeringDuration;
  unsigned long explodingDuration;
  unsigned long wakeupTime;
  double explodingSpeed;
  ice_state state;
};

class IceCrystalsMode{
  private:
    int count;
    ice_data ice[ICE_COUNT];
    void initializeIce(int a);
  public:
    IceCrystalsMode(int pCount);
    void loop(struct rgb *leds);
    void init();
};

int random(int min, int max)
{
  return (rand()%(max-min))+min;
}

IceCrystalsMode::IceCrystalsMode( int pCount){
  count = pCount;
}
void IceCrystalsMode::init(){
  for (int a=0;a<ICE_COUNT;a++){
    initializeIce(a);
    if(random(0,100)>60){
      ice[a].state = ICE_SLEEPING; 
      ice[a].wakeupTime = millis()+random(1000,2000);
    }
  }
}
void IceCrystalsMode::initializeIce(int  a){
  ice[a].position = random(10,1000)/1000.0f;
  ice[a].growingSpeed = millis()+random(500,1200);
  ice[a].flickeringDuration = ice[a].growingSpeed+random(2000,5000);
  ice[a].explodingDuration = ice[a].flickeringDuration+random(600,1800);
  ice[a].explodingSpeed = random(10,1000)/1000000.0f;
  ice[a].wakeupTime = ice[a].explodingDuration+random(200,400);
  ice[a].state = ICE_GROWING;
  ice[a].start = millis();
}

void IceCrystalsMode::loop(struct rgb *leds){
  struct rgb color;

  color.r = random(0,255);
  color.g = random(0,255);
  color.b = random(0,255);
  for(int whiteLed = 0; whiteLed < count; whiteLed = whiteLed + 1) {
    leds[whiteLed].g = constrain(9.8*leds[whiteLed].g/10.0-1, 0, 255);
    leds[whiteLed].r = constrain(9.8*leds[whiteLed].r/10.0-1, 0, 255);
    leds[whiteLed].b = constrain(9.8*leds[whiteLed].b/10.0-1, 0, 255);
  }
  for (int a=0;a<ICE_COUNT;a++){
    struct rgb *led = &leds[(int)round(ice[a].position*count)];
    struct rgb *ledr;
    struct rgb *ledl;
    int r, l;
    double npr, npl;
    int flicker = random(10,50);
    switch(ice[a].state){
      case ICE_GROWING:
        led->g = ((millis()-ice[a].start)*50)/(ice[a].growingSpeed-ice[a].start+1);
        led->r = ((millis()-ice[a].start)*70)/(ice[a].growingSpeed-ice[a].start+1);
        led->b = ((millis()-ice[a].start)*200)/(ice[a].growingSpeed-ice[a].start+1);
        if (millis()>ice[a].growingSpeed){
          ice[a].state = ICE_FLICKERING;
        }
        break;
      case ICE_FLICKERING: 
        led->g = flicker+50;
        led->r = flicker+70;
        led->b = flicker+200;
        if (millis()>ice[a].flickeringDuration){
          ice[a].state = ICE_EXPLODING;
        }
        break;
      case ICE_EXPLODING: 
        
        //led->b = 100-((millis()-ice[a].flickeringDuration)*100)/(ice[a].explodingDuration/10-ice[a].flickeringDuration);
        //led->r = 100-((millis()-ice[a].flickeringDuration)*100)/(ice[a].explodingDuration/10-ice[a].flickeringDuration);
        //led->g = 100-((millis()-ice[a].flickeringDuration)*100)/(ice[a].explodingDuration/10-ice[a].flickeringDuration);
        npr = ice[a].position+(ice[a].explodingSpeed*(millis()-ice[a].flickeringDuration));
        npl = ice[a].position-(ice[a].explodingSpeed*(millis()-ice[a].flickeringDuration));
        r = round(npr*count);
        l = round(npl*count);
        if(r>=0 && r<count){
          ledr = &leds[r];
          ledr->g = 0;
          ledr->r = 0;
          ledr->b = 10;
        }
        if(l>=0 && l<count){
          ledl = &leds[l];
          ledl->g = 0;
          ledl->r = 0;
          ledl->b = 10;
        }
        if (millis()>ice[a].explodingDuration){
          ice[a].state = ICE_SLEEPING;
        }
        break;
      case ICE_SLEEPING: 
        if (millis()>ice[a].wakeupTime){
          initializeIce(a);
        }
        break;
    }
  }
}

void ctrl_icecrystals()
{
  int nsdelay = 1000000/60;
  IceCrystalsMode ice(MAXLEDS);
  ice.init();

  while (1) {
    ice.loop(&ledbuffer[0]);
    flushbuffer();
    usleep(nsdelay);
  }
}

