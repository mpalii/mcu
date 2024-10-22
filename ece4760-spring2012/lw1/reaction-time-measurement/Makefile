# Makefile
# Properties
DESTINATION = firmware
DEVICE      = atmega644
PARTNUMBER  = m644
PROGRAMMER  = usbasp
INCLUDES	= $(addprefix -I, ./src/)
DEFINES	    = $(addprefix -D, F_CPU=20000000ULL BAUD_RATE=9600UL U2X DEFAULT_SCORE=9999UL SCORE_EEPROM_ADDRESS=0x0000)

# Utilities
AVRDUDE     = avrdude -c $(PROGRAMMER) -p $(PARTNUMBER)
AVRGCC      = avr-gcc -mmcu=$(DEVICE) -Os -Wall $(DEFINES) $(INCLUDES)
AVROBJCOPY  = avr-objcopy --input-target elf32-avr --output-target ihex --verbose
AVROBJDUMP  = avr-objdump --disassemble
AVRSIZE     = avr-size --format=AVR --mcu=$(DEVICE)

# Source files
SOURCES = 								\
    src/main.c 							\
										\
	src/drivers/gpio.c					\
	src/drivers/uart.c					\
	src/drivers/led.c					\
	src/drivers/button.c				\
	src/drivers/reset.c					\
	src/drivers/lcd.c					\
	src/drivers/system_timer.c			\
	src/drivers/buzzer.c				\
										\
	src/app/launcher.c					\
	src/app/metrics.c					\
	src/app/events.c					\
	src/app/messages.c					\
										\
	src/app/scheduler.c					\
	src/app/task/button_handler.c		\
	src/app/task/lcd_renderer.c			\
	src/app/task/state_resolver.c		\
	src/app/task/serial_writer.c		\
										\
	src/app/state_machine.c				\
	src/app/state/pre_ready.c			\
	src/app/state/before_fast_mode.c	\
	src/app/state/ready.c				\
	src/app/state/pre_wait.c			\
	src/app/state/wait.c				\
	src/app/state/pre_measuring.c		\
	src/app/state/measuring.c			\
	src/app/state/after_fast_mode.c		\

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

fuses-no-divider-int-rc:
	@$(AVRDUDE) -U lfuse:w:0xe2:m -U hfuse:w:0x99:m -U efuse:w:0xff:m 

fuses-no-divider-ext-clk:
	@$(AVRDUDE) -U lfuse:w:0xf7:m -U hfuse:w:0x99:m -U efuse:w:0xff:m
