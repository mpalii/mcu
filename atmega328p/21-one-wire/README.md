### DS18B20 Programmable Resolution 1-Wire® Digital Thermometer

#### TRANSACTION SEQUENCE
The protocol for accessing the DS18B20 via the 1-Wire port is as follows:  
- Initialization;  
- ROM Function Command;  
- Memory Function Command;  
- Transaction/Data.  

See also:  
- [DS18B20 datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Temp/DS18B20.pdf)  
- [Application Note 27](https://pdfserv.maximintegrated.com/en/an/AN27.pdf)  
- [Cyclic redundancy check](https://en.wikipedia.org/wiki/Cyclic_redundancy_check)  
- [CRC calculation for DS18B20](https://forum.arduino.cc/t/help-coding-crc-calulation-for-ds18b20-temperature-sensor/535661/1)  
- [Циклический избыточный код](https://ru.wikipedia.org/wiki/%D0%A6%D0%B8%D0%BA%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B8%D0%B7%D0%B1%D1%8B%D1%82%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4)  
- [uint8_t OneWire::crc8(const uint8_t *addr, uint8_t len)](https://github.com/PaulStoffregen/OneWire/blob/master/OneWire.cpp#L537)  
