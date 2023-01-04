# chASM - Control Hardware /with/ ASM 
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

Using unary shifts per execution, speed increased to 12.74KHz. this effect stayed  
even when the txBit() and latch() functions are being called. I am happy with this :)  

--------------------------------------------------------------------------------
This software is under the GPL v3 licence by ADBeta 2022. please read the
LICENCE file
