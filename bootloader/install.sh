#!/usr/bin/env bash

#avrdude: safemode: Fuses OK (E:FE, H:98, L:E0)
#avrdude -p m328pb -c xplainedmini -U hfuse:w:0x98:m
#avri-U lfuse:w:0xe0:m -U efuse:w:0xfe:m
avrdude -p m328pb -c xplainedmini -U flash:w:main.hex:i
avrdude -p m328pb -c xplainedmini -U eeprom:w:eeprom.bin:r

