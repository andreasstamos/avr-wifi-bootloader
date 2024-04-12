MCU = atmega328pb
F_CPU = 16000000UL

CC = avr-gcc
LD = avr-ld
OBJCOPY = avr-objcopy

PACK_FOLDER=../pack
COMMON_FOLDER=common

CFLAGS = -Wall -Wextra -B$(PACK_FOLDER)/gcc/dev/atmega328pb -I$(PACK_FOLDER)/include -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wl,--gc-sections -Os -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -gdwarf-3
LDFLAGS = -B$(PACK_FOLDER)/gcc/dev/atmega328pb -mmcu=$(MCU)

all: deploy

# These are just for the example!
$(COMMON_FOLDER)/lcd.o: CFLAGS += -DLCD_PCA9555
main: $(COMMON_FOLDER)/lcd.o $(COMMON_FOLDER)/twi_pca9555.o

main.hex: main
	avr-objcopy -O ihex main main.hex

deploy: main.hex
	python3 server.py main.hex

install: main.hex
	avrdude -p m328pb -c xplainedmini -U flash:w:main.hex

clean:
	rm -f main main.hex main.o ${COMMON_FOLDER}/lcd.o  ${COMMON_FOLDER}/twi_pca9555.o

.PHONY: all install clean

