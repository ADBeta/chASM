#include "chASM.h"

chASM p(8);

void setup() {
	p.setMode(OUTPUT);
}

void loop() {
	p.write(HIGH);
	p.write(LOW);

}
