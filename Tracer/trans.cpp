#include "trans.h"


void transistion::init(Adafruit_NeoPixel *str)
{
  strip_ptr = str;
}

void transistion::fadeDown()
{
  uint32_t c = 0;
  uint8_t steps = MAX_COLOUR;
  for (uint8_t z = 0; z < MAX_COLOUR; z++) 
  {
    c = strip_ptr->Color(0, steps, 0);
    
    util.setAll(c, strip_ptr);
    strip_ptr->show();
    steps--;
    delay(FADE_TIME);
  }
}

void transistion::fadeUp()
{
  uint32_t c = 0;
  uint8_t steps = 0;
  for (uint8_t z = 0; z < MAX_COLOUR; z++) 
  {
    c = strip_ptr->Color(0, steps, 0);
    
    util.setAll(c, strip_ptr);
    strip_ptr->show();
    steps++;
    delay(FADE_TIME);
  }
}

