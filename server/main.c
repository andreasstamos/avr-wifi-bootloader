#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common/lcd.h"

int main(void) {
	static const uint8_t msg1[] = "Hello! I am the";
	static const uint8_t msg2[] = "net program!";


	DDRB = 0xff;
	PORTB = 0xf0;
	
	lcd_init();
	lcd_data_buf(msg1, sizeof(msg1)-1);
	lcd_goto_line2();
	lcd_data_buf(msg2, sizeof(msg2)-1);


	DDRB = 0xff;
	PORTB = 0xf0;
	while (1) {
		PORTB = ~PORTB;
		_delay_ms(1500);
	}

	return 0;
}

