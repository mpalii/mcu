### Example 03 - EXTERNAL PULL-UP resistor is used, R = 20kΩ 

Scheme:  
<img src="scheme/simulation.jpeg">  

Breadboard:  
<img src="scheme/breadboard.jpg">  

**SIMULATION:** No simulation issues in SimulIDE  
**REALTIME:** The start is fine, several hits on the button are accompanied by a bounce, ignoring the pull-up resistor leads to the high-impedance state of a button pin, and LEDs start to blink randomly until button will be pushed  