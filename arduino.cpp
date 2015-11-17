// Implementing some functions Arduino has
#include <stdlib.h>
#include <sys/time.h>

long millis()
{
  struct timeval ts;
  gettimeofday(&ts, NULL);
  long ms = ts.tv_sec*1000 + ts.tv_usec/1000;
  return ms;
}

int constrain(int val, int min, int max)
{
  if (val <= min)
    return min;
  if (val >= max)
    return max;
  return val;
}

int random(int min, int max)
{
  return (rand()%(max-min))+min;
}

