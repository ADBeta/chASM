//***** ~1.5us - 610KHz ********************//
#include "chASM.h"

chASM pin(8);

void setup() {
	pin.setMode(OUTPUT);
}

void loop() {
	pin.write(HIGH);
	//pin.write(LOW);
}
