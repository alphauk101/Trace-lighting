#include "Adafruit_NeoPixel.h"
#include "phaseloop.h"
#include "trans.h"
#include "utils.h"
#include "nightride.h"
#include "police.h"
#include "defines.h"
#include "TimerOne.h"
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

efct_phaseloop e_phaseloop;/*just loops round*/
//efct_nightride e_nightride;
transistion e_trans;/*simple transtions*/
utils util;


#define YELLOW_LIMIT        130
#define MAX_LED             255 /*Max value a led can be*/

typedef uint8_t S_COLOUR;
#define GREEN   0
#define YELLOW  1
#define RED     2


volatile S_COLOUR s_colour;
volatile uint32_t s_output;
volatile int g_MicLevel = 0;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Trace started");
#endif
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  /*Timer*/
  Timer1.initialize(MIC_TIMER_INT); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

  strip.begin();

  /*initaite the startup*/

  e_trans.init(&strip);

  e_trans.fadeUp();
  e_trans.fadeDown();
  e_trans.fadeUp();
  e_trans.fadeDown();
  e_trans.fadeUp();
  /*We slowly faded up and waited appropriately we can now start the main loop*/
  delay(EFFECT_HOLD_SECS * 1000);
  /*now do the loop scan*/
  e_trans.fadeDown();

  s_colour = GREEN;
}

void loop() {

#ifdef bob
  e_phaseloop.start_effect(&strip);

  delay(EFFECT_HOLD_SECS * 1000);
  e_trans.fadeDown();

  e_nightride.start_effect(&strip);


  /*It is better to hold the effect for sometime or else we risk looking a bit OTT*/
  delay(EFFECT_HOLD_SECS * 1000);
  e_trans.fadeDown();
#endif

  set_all_green();
  delay(10);

}

volatile uint32_t red,green;
uint32_t get_colour(int level)
{
  red = 0;
  green = 0;
  /*we need to start to add red at a certain threshold then once past a nother threshold start
  removing green.*/

  if(level > YELLOW_LIMIT){
    red  = map((level - YELLOW_LIMIT), 0, (MAX_LED - YELLOW_LIMIT), 0, MAX_LED);  
    green = map((MAX_LED - level), 0, (MAX_LED - YELLOW_LIMIT), 0, MAX_LED );
  }else{
    /*We can assume this is a easy green so*/
    green = map(level, 0, YELLOW_LIMIT, 0, MAX_LED );
   }
  
  return strip.Color(red,green,0);  
}

void set_all_green()
{
  int level = getLevel();
  s_output = get_colour(level);

  util.setAll(s_output, &strip);
  strip.show();
}


int getLevel()
{
   //Serial.println(g_MicLevel);
  if(g_MicLevel > 450)g_MicLevel=450;
  return map(g_MicLevel, 0, 450, 0, MAX_LED);
}

/*Microphone timer ISR*/
int tmp_lvl;
void timerIsr()
{
  tmp_lvl = analogRead(MIC_AIO);
  if(tmp_lvl > g_MicLevel){
    g_MicLevel = tmp_lvl;
  } else {
    if (g_MicLevel > 0) g_MicLevel--;
  }
  //Serial.println(g_MicLevel);
}





