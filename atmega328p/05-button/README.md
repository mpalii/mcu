### Button, debounce, EMI

This section contains several examples with button handling, contact bounce, hardware debounce solution with RC circuit, and EMI (electromagnetic interference).  
According to the section 28.2 "DC Characteristics" of the datasheet the resistance of internal pull-up resistor is about [20; 50]kΩ.  

**IMPORTANT!!! Examples 03, 04, 05 and 06 are EMI sensitive.**  

In conditions of strong electromagnetic interference, you need to reduce the resistance of the pull-up / pull-down resistor.  
Increasing the resistance of pull-up / pull-down resistor reduces power consumption.  
Default resistance of pull/up / pull-down resostor 20kΩ (10kΩ or 1kΩ - in case of strong EMI).  

See also:  
- [28.2 DC Characteristics (Continued)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#G1411985)  
- [RC circuit](https://en.wikipedia.org/wiki/RC_circuit)  
- [RC time constant](https://en.wikipedia.org/wiki/RC_time_constant)  
- [11 Myths About Switch Bounce/Debounce](https://www.electronicdesign.com/technologies/analog/article/21155418/logiswitch-11-myths-about-switch-bouncedebounce)  
- [A Guide to Debouncing](https://my.eng.utah.edu/~cs5780/debouncing.pdf)  
- [Debounce a Switch](https://www.youtube.com/watch?v=e1-kc04jSE4&t)  
- [EMI](https://en.wikipedia.org/wiki/Electromagnetic_interference)  
