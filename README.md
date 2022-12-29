# chASM - Control Hardware /with/ ASM 
<b> (c) ADBeta 2022 </b>

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


## Changelog
* 2.0.1 - Added better readibilty.
<<<<<<< HEAD
* 2.1.2 - Added speed tests, bugfixed.
=======
* 2.1.0 - Added speed tests, bugfixed.
>>>>>>> 990a6de (refactor)
* 2.1.4 - Improved the speed_test example.
* 3.1.4 - Changed how the Bitmasking worked, so bitwise inversion isn't done  
every time the functions are called. This increased speed by another 2x

--------------------------------------------------------------------------------
This software is under the GPL v3 licence by ADBeta 2022. please read the
LICENCE file
