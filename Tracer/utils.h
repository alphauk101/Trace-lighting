#ifndef UTILS
#define UTILS
#include "defines.h"
#include "Adafruit_NeoPixel.h"


class utils{
  public:
  void setAll(colour, Adafruit_NeoPixel*);
  void allOff(Adafruit_NeoPixel *);
};


#endif
