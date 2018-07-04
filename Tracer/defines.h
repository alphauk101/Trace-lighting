#ifndef DEFINES
#define DEFINES
#include <stdio.h>

typedef uint32_t colour;


#define DEBUG

#define MIC_TIMER_INT     5000 /*Microseconds*/
#define MIC_AIO           A5

#define PIN 5 /*led data out pin*/

#define MIN_COLOUR        0
#define MAX_COLOUR        255

#define BOTTOM_CENTER     17 /*which led is the center*/

/*transtion fade time*/
#define FADE_TIME         1

//#define EFFECT_HOLD_SECS  30
#define EFFECT_HOLD_SECS  3

#endif
