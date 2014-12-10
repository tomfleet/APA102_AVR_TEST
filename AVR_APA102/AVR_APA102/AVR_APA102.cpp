/*
* Light_APA102 library example - AVR_APA102
*
* cycles a strip of APA102 through the HSV colour wheel.
*
* This example is configured for an ATMEGA328p, w/ external Oscillator @ 16MHz.
*/


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//include the external "C" APA102 funcitons
extern "C" {
	#include "light_apa102.h"
	}
	
//include the RGBConverter class
#include "RGBConverter.h"

// Number of LEDs
#define numLEDs 80

// LED Data 
struct cRGB ledFrame[numLEDs];

// uint8_t array for doing RGB/HSV calcs.
uint8_t rgb[3] = {0,0,0};


int main(void)
{
	// new RGB converter class
	RGBConverter rgbConv;
	
	// saturation and variance 	
	double sat= 1.0;
	double var = 1.0;
	while(1)
	{		
		for(float rotation = 0; rotation < 1; rotation += 0.01)	//cycle round the hue wheel
			{
				rgbConv.hsvToRgb(rotation, sat, var, rgb); //do rgb conv based on current hue, sat and var.
				for(int ledCount = 0; ledCount < numLEDs; ledCount+=1)	
					{
						//paint the entire strip with the RGB from the current HSV
						ledFrame[ledCount].r=rgb[0];ledFrame[ledCount].g=rgb[1];ledFrame[ledCount].b=rgb[2];    // Write red to array
					}
				//push the LED frame out to the LEDs
				apa102_setleds(ledFrame,numLEDs);
				//slow down a bit, so we can actually see something other than a flicker!
				_delay_ms(20);
			}
	}
}


