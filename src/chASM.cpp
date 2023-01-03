/*    chASM - control hardware /with/ ASM
* Low level hardware control library using Direct Port Manipulation.
*
* The safety features of the Arduino system calls are abandoned in return for 
* added speed and efficiency.
* Please read the README.md file for more information
* 
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/chASM
*	
* Version 3.2.5
* 29 Dec 2022
* (c) ADBeta
*/

#include "chASM.h"

//Initialise the assembly pin object and set all the internal vars
chASM::chASM(uint8_t pin) {
	//Set the internal variables using the builtin PROGMEM macros
	_asm_mask_nom = digitalPinToBitMask(pin); //Bitmask of chASM Pin (PGM)
	_asm_mask_inv = ~_asm_mask_nom; //Invert the Bitmask to use during exec
		
	_asm_port = digitalPinToPort(pin); //Port byte (PGM)
	
	_asm_ddr = portModeRegister(_asm_port); //Data Direction (volatile)
	_asm_opr = portOutputRegister(_asm_port); //Ouput Register (volatile)
	_asm_ipr = portInputRegister(_asm_port); //Input Register (volatile)
}

//Set the mode register of the pin
void chASM::setMode(uint8_t mode) {
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
void chASM::write(bool state) {
	while(true) {
		wh();
		wl();
	}
}

void chASM::wh() {
	*_asm_opr |= _asm_mask_nom; //Set mask bit in output register to HIGH
}

void chASM::wl() {
	*_asm_opr &= _asm_mask_inv; //Set mask bit in output register to LOW
}

//Read a binary state from the pin and return it
bool chASM::read(void) {
	//Read the input register and mask it. Simple comparation is faster than	
	//greater than/less than etc. If compare with 0 is true, the pin is LOW
	if((*_asm_ipr & _asm_mask_nom) == 0) {
		return 0;
	}
	
	//Return 1 if data is not 0
	return 1;
}
