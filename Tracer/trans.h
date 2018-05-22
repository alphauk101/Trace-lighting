#ifndef TRANS
#define TRANS
#include "utils.h"
#include "defines.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

class transistion {

  public:
    void init(Adafruit_NeoPixel *);
    void fadeUp(void);
    void fadeDown(void);
  private:
    utils util;
    Adafruit_NeoPixel *strip_ptr;
};



#endif
