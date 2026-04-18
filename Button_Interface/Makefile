# MCU and clock
MCU = atmega328p
F_CPU = 16000000UL

# Programmer
PROGRAMMER = usbasp

# Target file name (without extension)
TARGET = main

# Tools
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Compiler flags
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# Default target
all: $(TARGET).hex

# Compile
$(TARGET).elf: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).elf $(TARGET).c

# Convert to HEX
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

# Flash to MCU
flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET).hex:i

# Clean build files
clean:
	rm -f *.elf *.hex
