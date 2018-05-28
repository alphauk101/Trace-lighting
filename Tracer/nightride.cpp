#include "nightride.h"

#define CENTER    BOTTOM_CENTER;
#define TOP       29
#define BOTTOM    4

void efct_nightride::start_effect(Adafruit_NeoPixel* strip_ptr) {

  stp_ptr = strip_ptr;
  util.allOff(stp_ptr);
  this->do_effect();
  trans.fadeUp();
}

void efct_nightride::do_effect()
{
  /*Slide from side to side knight rider style*/
  uint8_t idx = CENTER;/*set to the center*/
  bool dir = true;
  uint8_t del = 50;

  uint8_t cdown = BOTTOM;
  uint8_t cup = TOP;

  for (int i = 0; i < 550; i++)
  {
    del = 25; /*set delay first*/
    if (dir)
    {
      idx++;
      if (idx == TOP) 
      {
        dir = false;
      }else{

      }
    } else {
      idx--;
      if (idx == BOTTOM) {
        dir = true;
      }else{

      }

    }

    this->set_leds(idx);
    stp_ptr->show();
    delay(del);
  }
}

void efct_nightride::set_leds(uint8_t index)
{
  /*When we get given a led index we need to work out which of the other leds are lit
    to give the faded effect*/

  /*first clear the strip*/
  util.allOff(stp_ptr);

  /*first set the index full*/
  stp_ptr->setPixelColor((index - 3), stp_ptr->Color(0, 5, 0));
  stp_ptr->setPixelColor((index - 2), stp_ptr->Color(0, 15, 0));
  stp_ptr->setPixelColor((index - 1), stp_ptr->Color(0, 100, 0));
  stp_ptr->setPixelColor(index, stp_ptr->Color(0, 255, 0));
  stp_ptr->setPixelColor((index + 1), stp_ptr->Color(0, 100, 0));
  stp_ptr->setPixelColor((index + 2), stp_ptr->Color(0, 15, 0));
  stp_ptr->setPixelColor((index + 3), stp_ptr->Color(0, 5, 0));
}

