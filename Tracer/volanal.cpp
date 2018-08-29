#include "volanal.h"

extern utils      g_util;

void volanal::init(Adafruit_NeoPixel * str_ptr){
  strip_ptr = str_ptr;
}


void volanal::vol_level(int level){

  /*Use the level to work out which LEDs to illuminate*/
  /*LED 17 is center at bottom - there are 16 leds in both directions*/
  /* There are 21 full steps from 17 before we hit max (top bar red)*/

  g_util.allOff(strip_ptr);

  
}

