# Makefile
# Properties
DESTINATION = firmware
DEVICE      = atmega1284
PARTNUMBER  = m1284
PROGRAMMER  = usbasp
INCLUDES	= $(addprefix -I, ./src/)
DEFINES	    = $(addprefix -D, F_CPU=18432000ULL)

# Utilities
AVRDUDE     = avrdude -c $(PROGRAMMER) -p $(PARTNUMBER)
AVRGCC      = avr-gcc -mmcu=$(DEVICE) -Os -Wall $(DEFINES) $(INCLUDES)
AVROBJCOPY  = avr-objcopy --input-target elf32-avr --output-target ihex --verbose
AVROBJDUMP  = avr-objdump --disassemble
AVRSIZE     = avr-size --format=AVR --mcu=$(DEVICE)

# Source files
SOURCES = 									\
    src/main.c 								\
											\
	src/drivers/gpio.c						\
	src/drivers/adc.c						\
	src/drivers/lcd.c						\
	src/drivers/timer_0.c					\
	src/drivers/button.c					\
											\
	src/system/events.c					    \
	src/system/launcher.c					\
	src/system/scheduler.c					\
	src/system/state_machine.c				\
											\
	src/system/task/button_handler.c	    \
	src/system/task/lcd_renderer.c			\
	src/system/task/state_resolver.c		\
											\
	src/system/state/vcc_measuring.c		\
	src/system/state/res_measuring_1k.c		\
	src/system/state/res_measuring_10k.c	\
	src/system/state/vol_measuring.c		\

# Object files
OBJECTS = $(patsubst src/%.c, target/%.o, $(SOURCES))

build: clean $(OBJECTS)
	@mkdir -p ./target  # Create the target directory if it doesn't exist
	@echo "Linking..."
	@$(AVRGCC) -o ./target/$(DESTINATION).elf $(OBJECTS)
	@$(AVROBJCOPY) ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

./target/%.o: ./src/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(AVRGCC) -c $< -o $@

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
	@$(AVROBJDUMP) ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@$(AVRSIZE) ./target/$(DESTINATION).elf 

fuses-default:
	@$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xff:m 

fuses-no-divider-ext-clk:
	@$(AVRDUDE) -U lfuse:w:0xf7:m -U hfuse:w:0x99:m -U efuse:w:0xff:m
