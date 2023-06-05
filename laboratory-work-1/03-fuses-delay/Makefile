# Makefile
SOURCE       = ./src/main.c
DESTINATION  = firmware
DEVICE       = atmega328p
PROGRAMMER   = usbasp-clone

default: build

build: clean 
	@mkdir target
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -o ./target/$(DESTINATION).elf $(SOURCE)
	@avr-objcopy --input-target elf32-avr --output-target ihex --verbose ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

check:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE)

erease:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -e

upload:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U flash:w:./target/$(DESTINATION).hex:i

disasm: ./target/$(DESTINATION).elf
	@avr-objdump -d ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@avr-size --format=AVR --mcu=$(DEVICE) ./target/$(DESTINATION).elf 

fuses-default:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

fuses-no-divider-int-rc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 
