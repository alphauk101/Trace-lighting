#include "nightride.h"

#define CENTER      BOTTOM_CENTER;
#define TOP         29
#define BOTTOM      4
#define TOTAL_LEDS  (TOP - BOTTOM)
#define SPEED       50
#define BACKGROUND  stp_ptr->Color(0, 100, 0)

void efct_nightride::start_effect(Adafruit_NeoPixel* strip_ptr) {

  stp_ptr = strip_ptr;
  util.allOff(stp_ptr);
  this->do_effect();
  trans.fadeUp();
}

void efct_nightride::do_effect()
{
  /*Slide from side to side knight rider style*/
  for (int i = 0; i < 100; i++)
  {
    this->goRight();
    delay(SPEED);
    this->goLeft();
    delay(SPEED);
  }
}


/*These functions scroll the light the way the knight rider does
  in the appropriate direction*/
void efct_nightride::goRight()
{
  uint8_t rightidx = TOP;
  /*Assumed that the LEDs are already scroled completely left
    so now scroll right*/
  for (int a = 0; a < TOTAL_LEDS; a++)
  {
    this->set_leds(rightidx, true);
    stp_ptr->show();
    delay(SPEED);
    rightidx--;
  }

}

void efct_nightride::goLeft()
{
  uint8_t leftidx = BOTTOM;
  /*Assumed that the LEDs are already scroled completely left
    so now scroll right*/
  for (int a = 0; a < TOTAL_LEDS; a++)
  {
    this->set_leds(leftidx, false);
    stp_ptr->show();
    delay(SPEED);
    leftidx++;
  }
}

void efct_nightride::set_leds(uint8_t index, bool goRight)
{
  /*When we get given a led index we need to work out which of the other leds are lit
    to give the faded effect*/

  /*first clear the strip*/
  //util.allOff(stp_ptr);
  util.setAll(BACKGROUND, stp_ptr);
  if (goRight) {
    /*knight rider there is a tail effect so*/
    stp_ptr->setPixelColor((index + 4), stp_ptr->Color(10,0,0));
    stp_ptr->setPixelColor((index + 3), stp_ptr->Color(50,0,0));
    stp_ptr->setPixelColor((index + 2), stp_ptr->Color(50,0,0));
    stp_ptr->setPixelColor((index + 1), stp_ptr->Color(100,0,0));
    stp_ptr->setPixelColor(index, stp_ptr->Color(MAX_COLOUR, 0, 0));
  } else {
    stp_ptr->setPixelColor((index - 4), stp_ptr->Color(10,0,0));
    stp_ptr->setPixelColor((index - 3), stp_ptr->Color(50,0,0));
    stp_ptr->setPixelColor((index - 2), stp_ptr->Color(75,0,0));
    stp_ptr->setPixelColor((index - 1), stp_ptr->Color(100,0,0));
    stp_ptr->setPixelColor(index, stp_ptr->Color(MAX_COLOUR,0,0));
  }
}

