#include "startburn.h"



void efct_startburn::start_effect(Adafruit_NeoPixel * sp)
{
  strip_ptr = sp;
  /*First slowly fade up all LEDs to green (Luckily the green is a good match to the trace green)*/

  fadeup();/*fades up to full green*/
  /*This leaves us on full green so wait for a while theres no rush*/

}

void efct_startburn::fadeup()
{
  /*start at 0 and slowly fade up the green*/
  uint8_t fv = MIN_COLOUR;
  uint32_t colour;
  for (; fv < MAX_COLOUR; fv++)
  {
    colour = strip_ptr->Color(0, fv, 0);
    util.setAll(colour,strip_ptr);
    strip_ptr->show();
    delay(50);
  }
}


