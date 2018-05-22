#include "utils.h"




/*Sets all pixels but does not show it!*/
void utils::setAll(colour c, Adafruit_NeoPixel *sptr)
{
   for (uint16_t i = 0; i < sptr->numPixels(); i++) {
    sptr->setPixelColor(i, c);
  }
}
