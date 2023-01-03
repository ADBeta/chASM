//Make a mimic of a chASM object, just without the class and methods. this will
//see if there is any inherant slowdown caused by class overhead.
//***** ~1us - 1.133MHz ********************//
// 85% Improvement!!!!!

uint8_t _asm_mask_nom; //Bitmask of the chASM pin - Normal form, eg 00010
uint8_t _asm_mask_inv; //Bitmask inverted eg 11101

uint8_t _asm_port; //Which hardware port the pin belongs to

volatile uint8_t *_asm_ddr; //Data Direction Register (for input/output)
volatile uint8_t *_asm_opr; //Output register for the pin
volatile uint8_t *_asm_ipr; //Input register for the pin

void chASM(uint8_t pin) {
	//Set the internal variables using the builtin PROGMEM macros
	_asm_mask_nom = digitalPinToBitMask(pin); //Bitmask of chASM Pin (PGM)
	_asm_mask_inv = ~_asm_mask_nom; //Invert the Bitmask to use during exec
		
	_asm_port = digitalPinToPort(pin); //Port byte (PGM)
	
	_asm_ddr = portModeRegister(_asm_port); //Data Direction (volatile)
	_asm_opr = portOutputRegister(_asm_port); //Ouput Register (volatile)
	_asm_ipr = portInputRegister(_asm_port); //Input Register (volatile)
}
	
//Set the mode register of the pin
void setMode(uint8_t mode) {
	if(mode == OUTPUT) {
		*_asm_ddr |= _asm_mask_nom; //DDR bit to 1
	}
	
	if(mode == INPUT) { 
		*_asm_ddr &= _asm_mask_inv; //DDR bit to 0
		*_asm_opr &= _asm_mask_inv; //Output register to 0
	}
	
	if(mode == INPUT_PULLUP) {
		*_asm_ddr &= _asm_mask_inv; //DDR bit to 0
		*_asm_opr |= _asm_mask_nom; //Output register to 1
	}
}

//Write binary state to the pin
void write(bool state) {
	if(state == 0) {
		*_asm_opr &= _asm_mask_inv; //Set mask bit in output register to LOW
	} else {
		*_asm_opr |= _asm_mask_nom; //Set mask bit in output register to HIGH
	}
}

//Read a binary state from the pin and return it
bool read(void) {
	//Read the input register and mask it. Simple comparation is faster than	
	//greater than/less than etc. If compare with 0 is true, the pin is LOW
	if((*_asm_ipr & _asm_mask_nom) == 0) {
		return 0;
	}
	
	//Return 1 if data is not 0
	return 1;
}

void setup() {
  chASM(8);

	setMode(OUTPUT);

}

void loop() {
	write(HIGH);
	write(LOW);
}