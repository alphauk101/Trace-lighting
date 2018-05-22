#ifndef STARTBURN
#define STARTBURN
#include "defines.h"
#include "utils.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

/*This should only be called on startup and provides the intial "bootup" animation*/

class efct_startburn{
  utils util;

  public:
  void start_effect(Adafruit_NeoPixel*);
  private:
  void fadeup(void);


  Adafruit_NeoPixel *strip_ptr;
};


#endif
