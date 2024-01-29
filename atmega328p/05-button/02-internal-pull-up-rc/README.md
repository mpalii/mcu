### Example 02 - INTERNAL PULL-UP resistor is used; R = 20kΩ and C = 1µF is used for debouncing  
Scheme:  
<img src="scheme.jpeg">  

Equivalent circuit scheme:  
<img src="scheme_eq.jpeg">

Breadboard:  
<img src="photo.jpg">  

**SIMULATION:** LEDs is turned on at the beginning of a simulation in SimulIDE  
**REALTIME:** The start is incorrect: LEDs are turned on at the beggining. RC circuit for debounce is fine  

FIX: the internal pull-up resistor is placed before capacitor, it needs some time to become fully charged, so after internal pull-up resistor activation some delay is needed.  