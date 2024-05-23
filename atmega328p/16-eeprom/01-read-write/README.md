# EEPROM  

To read the EEPROM section memory and create a dump as a raw binary 'eepromdump' file:  
`avrdude -c usbasp-clone -p atmega328p -U eeprom:r:eepromdump`  

To check the content:  
`hexdump - C eepromdump`  
`xxd eepromdump`  

To read the EEPROM section memory and create a dump as an intel format file 'eepromdump':  
`avrdude -c usbasp-clone -p atmega328p -U eeprom:r:eepromdump:i`   

To write the raw data to EEPROM section memory:  
`avrdude -c usbasp-clone -p atmega328p -U eeprom:w:eepromdump:r`  

See also:  
- [EEPROM](https://en.wikipedia.org/wiki/EEPROM)  
- [Section 8.4 "EEPROM Data Memory"](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf#G3.1181127)  
