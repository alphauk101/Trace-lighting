#include "Adafruit_NeoPixel.h"
#include "startburn.h"
#include "phaseloop.h"
#include "utils.h"
#include "defines.h"
#ifdef __AVR__
#include <avr/power.h>
#endif


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(76, PIN, NEO_GRB + NEO_KHZ800);


/*Each effect has its own file to keep things easier, each effect must have a start_effect() public function
this will start the effect and block until complete (some effects may have other functions but this is mandatory.
Effects will assume the lighting is properly setup ready to go*/

efct_startburn e_startburn;/*This effect is only intended for startup*/
efct_phaseloop e_phaseloop;/*just loops round*/

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Trace started");
#endif
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();

  /*initaite the startup*/
  e_startburn.start_effect(&strip);

  /*We slowly faded up and waited appropriately we can now start the main loop*/
  delay(EFFECT_HOLD_SECS * 1000);
  /*now do the loop scan*/
}

void loop() {

  
  e_phaseloop.start_effect(&strip);
  

  /*It is better to hold the effect for sometime or else we risk looking a bit OTT*/
  delay(EFFECT_HOLD_SECS * 1000);
}

void setAllLeds(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
}

void dotChase(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.clear();
    strip.setPixelColor(i++, c);
    strip.setPixelColor(i++, c);
    strip.setPixelColor(i++, c);
    strip.show();
    delay(wait);
  }
}

void doubleDotChase(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.clear();
    //dot one
    strip.setPixelColor(i++, c);
    strip.setPixelColor(i++, c);
    strip.setPixelColor(i++, c);


    strip.show();
    delay(10);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
