# chASM - Control Hardware /with/ ASM 
<b> (c) ADBeta 2022  2023</b>

chASM is an Arduino library to allow very fast hardware control using assembly  
and Direct Port Manipulation. This is ideal for projects that require high  
speed digital hardware control.  
Support for the low-sped MCUs (ATTiny series) -should- be baked in and is  
intended to be used, Please let me know if this is not the case, and if you  
come across any other problems.  

This library is designed to be as fast as possible, not intended to be a drop in  
replacement for the default system calls  such as pinMode, digitalWrite and  
digitalRead.

The safeties implied with the default system calls do not exist - and care must  
be taken when using this library. Speed is the highest priority, not protection.  

## Usage
All chASM Pins are treated as objects, this is to keep all the information and  
reference bytes in RAM - avoiding slow reads from PGM aka EEPROM every time the  
functions are called (such as happens in digitalWrite etc).  

To declare a chASM Pin -  
`chASM pinName(pinNumber);`

To set the mode of the chASM Pin -  
`pinName.setMode(t_MODE);`

To Write a bit to the chASM Pin -  
`pinName.write(0 or 1);`

To Read a bit from the chASM Pin -  
`pinName.read();`

To use chASM inside another class, i.e. to use chASM instead of digitalRead/Write  
inside another library, can be done via pointers and static declarations.  
NOTE: Include chASM.cpp and chASM.h in the src directory of any library you make  
and chASM can be portable to any host, project or library.  
```
//inside class or library scope
struct extScope {
	chASM *pin;

	void setPin(int pName) {
		//Create static chASM object with name ref_pin
		static chASM ref_pin(pName);
		
		//Set *pin to point to ref_pin 
		pin = &ref_pin;
	}
};

extScope.setPin(13);

//Write a high output to the pin pointer in extScope
extScope.pin->setMode(OUTPUT);
extScope.pin->write(HIGH);
```

Another method to do the same thing is to use the `new` operator. This is not  
recommended in Arduino, as it implies a large heap allocation, but it is easier  
to use and more understandable.
```
//inside class or library scope
struct extScope {
	chASM *pin;

	void setPin(int pName) {
		//Create new chASM object referring to pointer.
		pin = new chASM(pName);
	}
};

extScope.setPin(13);

//Write a high output to the pin pointer in extScope
extScope.pin->setMode(OUTPUT);
extScope.pin->write(HIGH);
```

For more information about using chASM for undefined until constructed uses, such  
as in libraries or classes etc, see the 'library_demo' example.  

## TODO
* Look into timers being altered by this library.  
* Look into analogRead support for this library.  
* Repeat speed tests in a more detailed manner, using a frequency counter.  

## Changelog
* 2.0.1 - Added better readibilty.  
* 2.1.0 - Added speed tests, bugfixed.  
* 2.1.4 - Improved the speed_test example.  
* 3.1.4 - Changed how the Bitmasking worked, so bitwise inversion isn't done  
every time the functions are called. This increased speed by another 2x  
* 3.2.4 - Refined functionality supporting external pointer to chASM, and added  
to Usage  
* 3.2.5 - Added an external library example in the examples dir.  

--------------------------------------------------------------------------------
This software is under the GPL v3 licence by ADBeta 2022. please read the
LICENCE file
