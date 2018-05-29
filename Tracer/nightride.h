#ifndef __NIGHTRIDE__
#define __NIGHTRIDE__
#include "utils.h"
#include "defines.h"
#include "trans.h"

class efct_nightride
{
    utils util;
    transistion trans;
    Adafruit_NeoPixel *stp_ptr;
  public:
    void start_effect(Adafruit_NeoPixel*);
  private:
    void goRight(void);
    void goLeft(void);
    void do_effect(void);
    void set_leds(uint8_t, bool);
};


#endif