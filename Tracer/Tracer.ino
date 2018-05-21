#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DEBUG
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(76, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Trace started");
#endif
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  colorWipe(strip.Color(0, 255, 0), 50); //

  delay(1000);

}
uint8_t spd = 50;
uint32_t c = 0;
uint8_t red, green, blue = 0;
void loop() {
  // put your main code here, to run repeatedly:
  dotChase(c, spd);



  if (spd == 0)
  {
    if (red != 255) {
      red++;
    } else {
      if (blue != 255)
        blue++;
    }

    setAllLeds(strip.Color(red, 255, blue));
    strip.show();
  } else {
    c = strip.Color(0, 255, 0);
    spd--;
  }
}

void setAllLeds(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i++, c);
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
