#ifndef PHASELOOP
#define PHASELOOP
#include "utils.h"
#include "defines.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif



class efct_phaseloop{
  utils util;

  public:
  void start_effect(Adafruit_NeoPixel*);

  private:
  void doloop(uint8_t,uint8_t);
  void setAll(colour);
  void fadeup(void);
  void goToWhite(void);
  void goToGreen(void);
  Adafruit_NeoPixel *strip_ptr;
};
#endif
