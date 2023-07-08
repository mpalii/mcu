# Makefile
DESTINATION  = firmware
DEVICE       = atmega328p
PROGRAMMER   = usbasp-clone
AVRDUDE      = avrdude -c $(PROGRAMMER) -p $(DEVICE)

default: build

build: clean
	@mkdir target
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -c ./src/uart328p.c -o ./target/uart328p.o
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -c ./src/main.c -o ./target/main.o
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -o ./target/$(DESTINATION).elf ./target/main.o ./target/uart328p.o
	@avr-objcopy --input-target elf32-avr --output-target ihex --verbose ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

check:
	@$(AVRDUDE)

erease:
	@$(AVRDUDE) -e

upload:
	@$(AVRDUDE) -U flash:w:./target/$(DESTINATION).hex:i

disasm: ./target/$(DESTINATION).elf
	@avr-objdump -d ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@avr-size --format=AVR --mcu=$(DEVICE) ./target/$(DESTINATION).elf 

fuses-default:
	@$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

fuses-no-divider-int-rc:
	@$(AVRDUDE) -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

fuses-no-divider-ext-clk:
	@$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
