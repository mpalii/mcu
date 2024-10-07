### Timer/Counter1 Compare Match A Interrupt

Timer/Counter1 is an 16-bit register (can hold values from 0 to 65535). The Prescaler value is set to 8. Internal RC Oscillator - 1MHz. Compare value - 12499. Max iterations - 10.  
Clear Timer on Compare or CTC mode choosen.    
fOCnA = fclk/(2\*N\*(1 + OCRnA)) - see page 88 of datasheet.  
Total period of the led toggling: (1/1000000)\*8\*(1 + 12499)\*10 = 1.000000s.  
Current limiting resistor - 300 Ohm.  
Supply voltage - 5V.  

**NOTE: In Clear Timer on Compare or CTC mode works with the OCR1A or ICR1 Register (see page 87 of datasheet). Below shown simulation result in Proteus:**  

 0.000000 -  1.100063		LED OFF  
 1.100064 -  2.100064		LED ON  
 2.100065 -  3.100063		LED OFF  
 3.100064 -  4.100064		LED ON  
 4.100065 -  5.100063		LED OFF  
 5.100064 -  6.100064		LED ON  
 6.100065 -  7.100063		LED OFF  
 7.100064 -  8.100064		LED ON  
 8.100065 -  9.100063		LED OFF  
 9.100064 - 10.100064		LED ON  
10.100065 - 11.100063		LED OFF  
11.100064 - 12.100064		LED ON  
12.100065 - ...				LED OFF  


<img src="Proteus/scheme.BMP">
