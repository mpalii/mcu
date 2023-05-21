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
	avrdude -c $(PROGRAMMER) -p $(DEVICE)

erease:
	avrdude -c $(PROGRAMMER) -p $(DEVICE) -e

upload:
	avrdude -c $(PROGRAMMER) -p $(DEVICE) -U flash:w:./target/$(DESTINATION).hex:i
