#include "chASM.h"

//Initialise the assembly pin object and set all the internal vars
chASM::chASM(uint8_t pin) {
	//Set the internal variables using the builtin PROGMEM macros
	this->_asm_mask = digitalPinToBitMask(pin); //Bit mask in port byte (PGM)
	this->_asm_port = digitalPinToPort(pin); //Port byte (PGM)
	
	this->_asm_ddr = portModeRegister(_asm_port); //Data Direction (volatile)
	this->_asm_opr = portOutputRegister(_asm_port); //Ouput Register (volatile)
	this->_asm_ipr = portInputRegister(_asm_port); //Input Register (volatile)
}

//Set the mode register of the pin
void chASM::setMode(uint8_t mode) {
	if(mode == OUTPUT) {
		*_asm_ddr |= _asm_mask; //DDR bit to 1
	}
	
	if(mode == INPUT) { 
		*_asm_ddr &= ~_asm_mask; //DDR bit to 0
		*_asm_opr &= ~_asm_mask; //Output register to 0
	}
	
	if(mode == INPUT_PULLUP) {
		*_asm_ddr &= ~_asm_mask; //DDR bit to 0
		*_asm_opr |= _asm_mask; //Output register to 1
	}
}

//Write binary state to the pin
void chASM::write(bool state) {
	if (state == 0) {
		*_asm_opr &= ~_asm_mask; //Set mask bit in output register to LOW
	} else {
		*_asm_opr |= _asm_mask; //Set mask bit in output register to HIGH
	}
}

//Read a binary state from the pin and return it
bool chASM::read(void) {
	//Read the input register and mask it. Simple comparation is faster than	
	//greater than/less than etc. If compare with 0 is true, the pin is LOW
	if((*_asm_ipr & _asm_mask) == 0) {
		return 0;
	}
	
	//Return 1 if data is not 0
	return 1;
}
