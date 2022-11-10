#include "chASM.h"

//Define a chASM Pin, Pin 13 aka the LED pin
chASM LED(13);

void setup() {
	//Set the pin to output
	LED.setMode(OUTPUT);
}

void loop() {
	//Write LED HIGH, then wait
	led.write(1);
	delay(1000);
	
	//Write LED LOW, then wait
	LED.write(0);
	delay(1000);
}
