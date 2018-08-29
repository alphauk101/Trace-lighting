#ifndef __VOLANAL__
#define __VOLANAL__
#include "utils.h"
#include "defines.h"
#include "Adafruit_NeoPixel.h"

/****************************
Volume Analyser - Starts from the bottom center and runs up the sides in parallel 
Typical volume to light effects of a spectrum analysier 

Bottom center LEDs are 15-16-17 and one side goes up with the volume one side will 
go down including a jump (could be interesting. 
****************************/
class volanal {
  public:
    void init(Adafruit_NeoPixel *);
    /*The level is passed here and we do the appropriate algorithms to display the LEDs*/
    void vol_level(int);
  private:
  Adafruit_NeoPixel *strip_ptr;
};
#endif
