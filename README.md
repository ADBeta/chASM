# chASM - Control Hardware /with/ ASM 
<<<<<<< HEAD
## Optimization chasing branch 
<b> (c) ADBeta  2023</b>

<b> This branch is chasing optimizations... Since testing the speed of chASM, which  
showed to be around 4x faster at best, and slowed down the more times the functions  
were called. - Having since then tested a Plain-Old-Data version of the library  
I can see that the back anf forth calling of - specifically class - functions  
is much slower desired.  

chASM Release 1 got a best case speed of 610KHz, and the P.O.D version got  
1.133MHz, an 85% improvement. (POD-Speed-test.ino).  

Multiple function calls per scope is still slower than desired.</b>  
=======
<b> (c) ADBeta 2023</b>

chASM is an Arduino library to allow very fast hardware control using Direct Port  
Manipulation. This is ideal for projects that require high speed digital hardware  
control.  

Support for the low-sped MCUs (ATTiny series) -should- be baked in and is  
intended to be used, Please let me know if this is not the case, and if you  
come across any other problems.  

This library is designed to be as fast as possible, so some of the methods are  
inlined, causing slightly higher Program Space Usage. Please keep this in mind.  

While this library *can* be used as a drop-in replacement for digitalRead, pinMode  
and digitalWrite, this is not completely recommended, as this library uses more  
Program Storage than the system default functions - It also does not have the safety  
checks and failmodes the system default options do.  
As such, this library is only recommended for slightly experienced programmers.  
>>>>>>> 6e46767 (v4.2.5)

Plan A) externalized calls with read and write. Pass variables to functions  
--- This did not work. Same speed as before  

Plan B) Inline functions  
--- Could be done but is very unreliable  

Omitting if test in write() increases speed by 50KHz  

Plan B was not fully realized because inlining on arduino is specific and weird.  
Test again with actual inlineing:  

--- Inlining write() makes it marginally faster, now the bottleneck is in loop()  
function calls. This is a good improvement. Each call to write() takes 17 bytes.  
- Each digitalWrite call takes 6 bytes. this is a 2.8% increase in PGRM space usage  

********************************************************************************
Testing mockup of SR595 using inlined function calls.  
chASM without inline: PRGM usage: 1038 Bytes / 66 Bytes   speed: 8.84KHz  
Inlined chASM: PRGM usage: 1082 Bytes / 66 bytes    speed: 10.15KHz  

This uses 4% more PRGM, for a 15% speed improvement. Is this an okay sacrifice?  

----
Using a different method in FastSR595, speed stayed the same. This is good enough  
proof that it is fast enough.  

<<<<<<< HEAD
Using unary shifts per execution, speed increased to 12.74KHz. this effect stayed  
even when the txBit() and latch() functions are being called. I am happy with this :)  
=======
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

## Notes
Speed Measurements:  
These tests have been conducted in a few ways, this is to try to get accurate  
estimates for common usecases. Some things cannot be avoided, such as the delay  
between `void loop() { }` loops. This is fair due to the average usecase; also  
because digitalRead will be used as a control, in the exact same manner.  

All tests have been conducted with a Racal-Dana 9914 VHF Freq. Counter, which has  
been calibrated to 8Hz standard deviation.  

Test Methods:  
```
void loop() {
	write( HIGH );
	write( LOW );
}
```
digitalWrite:  146.9KHz  
chASM:         610.5KHz    4.15x faster  

```
void loop() {
	write( HIGH );
	write( LOW );
	write( HIGH );
	write( LOW );
	(Repeat 5 times)
}
```
digitalWrite:  151.5KHz  
chASM:         409.9KHz    2.70x faster  

Conclusion:  
It seems that the class call overhead is relatively large. This library is still  
considerably faster than digitalRead/Write but is not very consistent amounts faster.  

## TODO
* Look into timers being altered by this library.  
* Look into analogRead support for this library.  
* Make Program Space overhead as small as possible. Optimize function size.  

## Changelog
* 2.0.1 - Added better readibilty.  
* 2.1.0 - Added speed tests, bugfixed.  
* 2.1.4 - Improved the speed_test example.  
* 3.1.4 - Changed how the Bitmasking worked, so bitwise inversion isn't done  
every time the functions are called. This increased speed by another 2x  
* 3.2.4 - Refined functionality supporting external pointer to chASM, and added  
to Usage  
* 3.2.5 - Added an external library example in the examples dir.  
* 4.2.5 - Inline solution to speed problem. End result of Optimize branch.  
>>>>>>> 6e46767 (v4.2.5)

--------------------------------------------------------------------------------
This software is under the GPL v3 licence by ADBeta 2023. please read the
LICENCE file
