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
/*Shows the intro animation a bit long for development*/
//#define SHOW_START

typedef uint8_t MODE;
#define STOL    0
#define DISCO   1
static MODE mode;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(76, PIN, NEO_GRB + NEO_KHZ800);


/*This is our array of 32bit colours*/
#define DIVISER 4
#define DISCO_TIME    50/*time in multiples of 10 ms how long each light is displayed for*/

#define CARRAY_LEN    4

/*Each effect has its own file to keep things easier, each effect must have a start_effect() public function
  this will start the effect and block until complete (some effects may have other functions but this is mandatory.
  Effects will assume the lighting is properly setup ready to go*/

efct_phaseloop e_phaseloop;/*just loops round*/
//efct_nightride e_nightride;
transistion e_trans;/*simple transtions*/
utils util;



#define YELLOW_LIMIT        130
#define MAX_LED             255 /*Max value a led can be*/

#define MODE_MIN            1000 /*10 secs*/  
#define MODE_MAX            30000

typedef uint8_t S_COLOUR;
#define GREEN   0
#define YELLOW  1
#define RED     2

volatile uint32_t disco_lights[DIVISER];
uint16_t disco_count = 0;
const uint32_t gColourArray[] = { 
                                 0x00FF0000,
                                 0x0000FF00,
                                 0x000000FF,
                                 0x00FFFF00,
                                 };
volatile S_COLOUR s_colour;
volatile uint32_t s_output;
volatile int g_MicLevel = 0;
uint16_t mode_count = 0;
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

#ifdef SHOW_START
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


  e_phaseloop.start_effect(&strip);

  delay(EFFECT_HOLD_SECS * 1000);
  e_trans.fadeDown();

  //e_nightride.start_effect(&strip);


  /*It is better to hold the effect for sometime or else we risk looking a bit OTT*/
  delay(EFFECT_HOLD_SECS * 1000);
  e_trans.fadeDown();
#endif

  /*Set default mode*/
  mode_count = random(MODE_MIN, MODE_MAX); 
  mode = STOL;
  //mode = DISCO;
}

void loop() {

  switch (mode)
  {
    case STOL:
      /*Sets the level in accordance to the sound level*/
      sound_to_light();
      break;
    case DISCO:
      show_disco();
      break;
    default:
      break;
  }
  delay(10);

  if(mode_count == 0)
  {
    mode_count = random(MODE_MIN, MODE_MAX); 
    if(mode==STOL){
      mode = DISCO;
    }else{
      mode = STOL;
    }
  }else{
    mode_count--;
  }
}

void show_disco()
{
  //First set our array of random colours
  //We only want to do this if we have displayed the same style for a length of time
  if(disco_count == 0){
    get_random_colours();
    /*reset counter*/
    disco_count = DISCO_TIME;
  }else{
    disco_count--;
  }

  //Our array should now have the colours set
  //Now apply these colours to the strip
  strip.clear();
  set_disco_strip();
  /*Set brightness is accordance to volume*/
  int level = getLevel();
  if(level < 50)level = 50;/*make sure we dont go completely off*/
  strip.setBrightness(level);
  
  strip.show();
  //Serial.println("update disco");
}


void set_disco_strip()
{
  uint8_t divc = 0;
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    if((i % (strip.numPixels()/DIVISER))==0)divc++;

    //strip.setPixelColor(i, disco_lights[divc]);
    strip.setPixelColor(i, disco_lights[divc]);
    //Serial.println(divc,DEC);
  }

}

void get_random_colours() {
  uint8_t r = 0;
  uint8_t prev = 0;
  for (int a = 0; a < DIVISER; a++)
  {
    //Reduce the chance of duplicate colours
    r = random(0, (CARRAY_LEN));
    if(r == prev){
      r = random(0, (CARRAY_LEN));
    }
    prev = r;

    
    disco_lights[a] = gColourArray[r];
    
    /*
    Serial.println(r,DEC);
    Serial.println(disco_lights[a],HEX);
    */
  }
}

volatile uint32_t red, green;
uint32_t get_colour(int level)
{
  red = 0;
  green = 0;
  /*we need to start to add red at a certain threshold then once past a nother threshold start
    removing green.*/

  if (level > YELLOW_LIMIT) {
    red  = map((level - YELLOW_LIMIT), 0, (MAX_LED - YELLOW_LIMIT), 0, MAX_LED);
    green = map((MAX_LED - level), 0, (MAX_LED - YELLOW_LIMIT), 0, MAX_LED );
  } else {
    /*We can assume this is a easy green so*/
    green = map(level, 0, YELLOW_LIMIT, 0, MAX_LED );
  }

  return strip.Color(red, green, 0);
}

void sound_to_light()
{
  int level = getLevel();
  s_output = get_colour(level);

  util.setAll(s_output, &strip);
  strip.show();
}


int getLevel()
{
  //Serial.println(g_MicLevel);
  if (g_MicLevel > 450)g_MicLevel = 450;
  return map(g_MicLevel, 0, 450, 0, MAX_LED);
}

/*Microphone timer ISR*/
int tmp_lvl;
void timerIsr()
{
  tmp_lvl = analogRead(MIC_AIO);
  if (tmp_lvl > g_MicLevel) {
    g_MicLevel = tmp_lvl;
  } else {
    if (g_MicLevel > 0) g_MicLevel--;
  }
  //Serial.println(g_MicLevel);
}





