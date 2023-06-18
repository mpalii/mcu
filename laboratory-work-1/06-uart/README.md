# UART  

TODO add description

mp@mp-HP-laptop:~/_Projects/ece4760-spring2012/laboratory-work-1/06-uart/01-byte-oriented/src$ avr-gcc -mmcu=atmega328p -Os -Wall -c uart328p.c
mp@mp-HP-laptop:~/_Projects/ece4760-spring2012/laboratory-work-1/06-uart/01-byte-oriented/src$ avr-gcc -mmcu=atmega328p -Os -Wall -c main.c
mp@mp-HP-laptop:~/_Projects/ece4760-spring2012/laboratory-work-1/06-uart/01-byte-oriented/src$ avr-gcc -mmcu=atmega328p -Os -Wall -o firmware.elf main.
main.c  main.o  
mp@mp-HP-laptop:~/_Projects/ece4760-spring2012/laboratory-work-1/06-uart/01-byte-oriented/src$ avr-gcc -mmcu=atmega328p -Os -Wall -o firmware.elf main.o uart328p.o
mp@mp-HP-laptop:~/_Projects/ece4760-spring2012/laboratory-work-1/06-uart/01-byte-oriented/src$ avr-objcopy --input-target elf32-avr --output-target ihex --verbose firmware.elf firmware.hex
copy from `firmware.elf' [elf32-avr] to `firmware.hex' [ihex]
mp@mp-HP-laptop:~/_Projects/ece4760-spring2012/laboratory-work-1/06-uart/01-byte-oriented/src$ avr-size --format=avr --mcu=atmega328p firmware.elf 

picocom --imap spchex,tabhex,crhex,lfhex,nrmhex,8bithex -b 9600 -r -l /dev/ttyUSB0  

picocom --flow none --baud 9600 --parity none --databits 8 --stopbits 1 --noreset --nolock --imap spchex,tabhex,crhex,lfhex,nrmhex,8bithex /dev/ttyUSB0
picocom --flow none --baud 9600 --parity none --databits 8 --stopbits 1 --noreset --nolock --echo /dev/ttyUSB0 
