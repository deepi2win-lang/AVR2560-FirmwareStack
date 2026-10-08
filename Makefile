MCU=atmega2560
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-mmcu=$(MCU) -Os -Wall -Iinclude
SRC=$(wildcard src/*.c)
APP?=main.c
ELF=main.elf
HEX=main.hex
all:
	$(CC) $(CFLAGS) $(SRC) $(APP) -o $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $(ELF) $(HEX)
clean:
	rm -f $(ELF) $(HEX)
