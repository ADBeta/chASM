#include <chASM.h>

struct demo {
	//A pointer to a chASM Object allows you to declare the chASM pin without
	//giving it a pin to construct the object before use. This is very useful
	//when you have to create a class or library without knowing what pins will
	//be used by the user, but wish to use chASM for its much higher speed.
	chASM *pin;

	//This funciton will create a static chASM object and reference it to the
	//pin pointer.
	void setPin(uint8_t pinName) {
		//Static object
		static chASM refPin(pinName);
		
		//Set pointer
		pin = &refPin;
		
		//Set output via pointer
		pin->setMode(OUTPUT);
	}
	
	//This function will write HIGH or LOW to the pin via its internal pointer.
	void writePin(bool state) {
		pin->write(state);
	}
	
} demo;

void setup() {
	//Until this point, chASM object *pin has had no idea what pin to use,
	//We can change this by setting the pin now.
	demo.setPin(13);

}

void loop() {
	//now we can blink the pin (LED) using the demo struct, not chASM directly.
	demo.writePin(HIGH);
	delay(1000);
	
	demo.writePin(LOW);
	delay(1000);	
}
