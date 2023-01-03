//***** ~1.5us - 610KHz ********************//
#include "chASM.h"

chASM pin(8);

void setup() {
	pin.setMode(OUTPUT);
}

void loop() {
	//pin.write(HIGH);
  //pin.write(LOW);

  //pin.write(LOW);

  digitalWrite(8, HIGH);
  //digitalWrite(8, LOW);

  //digitalWrite(8, HIGH);

}
