MCU = atmega328pb
F_CPU = 16000000UL

CC = avr-gcc
LD = avr-ld
OBJCOPY = avr-objcopy

PACK_FOLDER=../pack

CFLAGS = -Wall -Wextra -Wconversion -B$(PACK_FOLDER)/gcc/dev/atmega328pb -I$(PACK_FOLDER)/include -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wl,--gc-sections -Os -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -gdwarf-3
LDFLAGS = -B$(PACK_FOLDER)/gcc/dev/atmega328pb -mmcu=$(MCU) -Wl,-section-start=.stage2=0x200,-section-start=.text=0x7000

EEPROMSIZE = 1024

all: main.hex eeprom.bin

main_pre: common/usart.c common/esp8266.c main.c stage2/common/twi_pca9555.c stage2/common/lcd.c stage2/common/keypad.c
	cp stage2_arr_initial.c stage2_arr.c
	$(CC) $(LDFLAGS) $(CFLAGS) -DLCD_PCA9555 -o $@ $?

stage2.bin: main_pre
	avr-objcopy -O binary -j .stage2 main_pre stage2.bin

eeprom.bin: stage2.bin
	dd if=stage2.bin of=eeprom.bin bs=1 count=$(EEPROMSIZE)

stage2_arr.c: stage2.bin
	./bin_to_c.py stage2.bin stage2_arr.c stage2_bin $$(($(EEPROMSIZE)+1))

main: stage2_arr.c common/usart.c common/esp8266.c main.c stage2/common/twi_pca9555.c stage2/common/lcd.c stage2/common/keypad.c
	$(CC) $(LDFLAGS) $(CFLAGS) -DLCD_PCA9555 -o $@ common/usart.c common/esp8266.c main.c stage2/common/twi_pca9555.c stage2/common/lcd.c stage2/common/keypad.c

main.hex: main
	avr-objcopy -O ihex -j .text -j .data main main.hex

install: main.hex eeprom.bin
	./install.sh

clean:
	rm -f main_pre stage2.bin stage2_arr.c main

distclean: clean
	rm -f main.hex eeprom.bin


.PHONY: all install clean distclean

