/*
	This example is purely to objectively show and measure the speed difference
	between the built-in functions vs my library.
	
	An oscilloscope, frequency counter or some other form of external equipment
	in order to measure the signals.
	
	ADBeta 10 Nov 2022
*/

#include <chASM.h>

//Declare both pins, one is a chASM pin the other is a built-in pin
#define slowPin 10
chASM fastPin(9);

void setup() {
	//Configure both pins to be outputs
	fastPin.setMode(OUTPUT);
	pinMode(slowPin, OUTPUT);
	
	uint8_t state = 0;
	
	while(true) {
		/** Fast pin **/
		//fastPin.write(state);
		
		/** Slow Pin **/
		digitalWrite(slowPin, state);
		
		//Invert state to create the pulse
		state = ~state;
	}
}

void loop() {

}
