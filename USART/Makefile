# ===============================
# AVR Professional Makefile
# ===============================

# Project name
TARGET = main

# MCU
MCU = atmega328p

# Clock Frequency
F_CPU = 16000000UL

# Programmer
PROGRAMMER = usbasp
PORT = usb

# Tools
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

# Source files (auto-detect all .c files)
SRC = $(wildcard *.c)

# Object files
OBJ = $(SRC:.c=.o)

# Compiler flags
CFLAGS = -Wall -Wextra -Os -std=c99 -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# ===============================
# Default Target
# ===============================
all: $(TARGET).hex size

# ===============================
# Compile .c to .o
# ===============================
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# Link Object Files
# ===============================
$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET).elf

# ===============================
# Create HEX File
# ===============================
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

# ===============================
# Show Program Size
# ===============================
size: $(TARGET).elf
	$(SIZE) --mcu=$(MCU) --format=avr $(TARGET).elf

# ===============================
# Upload to AVR
# ===============================
flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:w:$(TARGET).hex:i

# ===============================
# Set Fuse Example
# ===============================
fuses:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) \
	-U lfuse:w:0xFF:m \
	-U hfuse:w:0xDA:m \
	-U efuse:w:0x05:m

# ===============================
# Clean Build Files
# ===============================
clean:
	rm -f *.o *.elf *.hex

# ===============================
# Rebuild Everything
# ===============================
rebuild: clean all
