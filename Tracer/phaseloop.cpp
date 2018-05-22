#include "phaseloop.h"


/*Lead tail effect defines*/
#define TA    strip_ptr->Color(0, MAX_COLOUR, 0)
#define TB    strip_ptr->Color(0, 200, 0)
#define TC    strip_ptr->Color(0, 150, 0)
#define TD    strip_ptr->Color(0, 125, 0)
#define TE    strip_ptr->Color(0, 100, 0)
#define TF    strip_ptr->Color(0, 75, 0)
#define TG    strip_ptr->Color(0, 50, 0)
#define TH    strip_ptr->Color(0, 25, 0)
#define TI    strip_ptr->Color(0, 10, 0)



void efct_phaseloop::start_effect(Adafruit_NeoPixel* strp) {
  strip_ptr = strp;

  /*simple effect that rotates the leds*/
  for (uint8_t a = 15; a > 0; a--)
  {
    this->doloop(a);
  }

  for (uint8_t a = 10; a > 0; a--)
  {
    this->doloop(0);
  }
  this->fadeup();
  /*Next appear to be fully on and burning up :)*/
  util.setAll(strip_ptr->Color(0, MAX_COLOUR, 0), strip_ptr);
  strip_ptr->show();
  delay(5000);
}

void efct_phaseloop::fadeup() {
  uint32_t c = 0;
  uint8_t loops = 75;
  uint8_t steps = (MAX_COLOUR - loops);

  for (uint8_t z = 0; z < loops; z++) {
    if ( (z % 2) == 0) {
      c = strip_ptr->Color(0, steps, 0);
      steps++;
    } else {
      c = strip_ptr->Color(0, 0, 0);
    }

    util.setAll(c, strip_ptr);
    strip_ptr->show();
    delay(loops - z);
  }
}

void efct_phaseloop::doloop(uint8_t spd)
{
  /*as we go round the loop we want there to be a faded - not faded - faded type of effect*/
  for (uint16_t x = strip_ptr->numPixels(); x > 0; x--) {
    strip_ptr->clear();
    strip_ptr->setPixelColor(x, TA);
    if ((x + 7) < strip_ptr->numPixels()) {
      strip_ptr->setPixelColor(x + 1, TC);
      strip_ptr->setPixelColor(x + 2, TD);
      strip_ptr->setPixelColor(x + 3, TE);
      strip_ptr->setPixelColor(x + 4, TF);
      strip_ptr->setPixelColor(x + 5, TG);
      strip_ptr->setPixelColor(x + 6, TH);
      strip_ptr->setPixelColor(x + 7, TI);
    }
    strip_ptr->show();
    delay(spd);
  }
}




