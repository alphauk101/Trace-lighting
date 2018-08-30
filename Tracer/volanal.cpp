#include "volanal.h"

#define CENTER_LED      17
#define NUM_STEPS       21

extern utils      g_util;
volatile uint8_t  vol_lvl;

void volanal::init(Adafruit_NeoPixel * str_ptr) {
  strip_ptr = str_ptr;

  vol_lvl = 0 ;
}


void volanal::vol_level(int level) 
{

  /*Use the level to work out which LEDs to illuminate*/
  /*LED 17 is center at bottom - there are 16 leds in both directions*/
  /* There are 21 full steps from 17 before we hit max (top bar red)*/

  strip_ptr->clear();

  //First thing we do is transform the level into number of steps
  vol_lvl = map(level, MIN_MIC, MAX_MIC, 0, NUM_STEPS);

  //Using the number of steps show this on the leds
  for (uint8_t a = CENTER_LED; a < (CENTER_LED+NUM_STEPS); a++)
  {
    if(vol_lvl >=  (a-CENTER_LED)){
      strip_ptr->setPixelColor(a,strip_ptr->Color(0, MAX_COLOUR, 0));
    }
  }
  strip_ptr->show();

}

