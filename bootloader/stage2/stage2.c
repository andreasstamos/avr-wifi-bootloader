#include <util/delay.h>

#include "common/lcd.h"
#include "common/keypad.h"

#include "stage2.h"

#include <avr/io.h>

//__attribute__((naked)) __attribute__((section(".ctors")))
__attribute__((section(".stage2")))
int get_ip_address(char *ipaddr) {
	DDRB = 0xFF;
	PORTB = 0x08;
	
	char *ipaddr_start = ipaddr;

	static uint8_t msg1[] = "ntuaAboard_G1";
	static uint8_t msg2[] = "WiFi Bootloader";
	static uint8_t msg3[] = "Enter IP Address";
	static uint8_t msg4[] = "* on .,# on end";
	static uint8_t msg5[] = "Server IP Addr:";

	lcd_init();
	keypad_init();

	lcd_clear_display();
	lcd_data_buf(msg1, sizeof(msg1)-1);
	lcd_goto_line2();
	lcd_data_buf(msg2, sizeof(msg2)-1);
	_delay_ms(2000);
	lcd_clear_display();
	lcd_data_buf(msg3, sizeof(msg3)-1);
	lcd_goto_line2();
	lcd_data_buf(msg4, sizeof(msg4)-1);
	_delay_ms(2000);
	lcd_clear_display();
	lcd_data_buf(msg5, sizeof(msg5)-1);
	lcd_goto_line2();

	for (uint8_t i=0; i<4; ++i) {
		for (uint8_t j=0; j<3; ++j) {
			char c;
			do c = keypad_to_ascii(); while (!( (((j != 0) ? '0' : '1')<=c && c<='9') || (c == '*' && i<=2) | (c=='#' && i==3 && j>=1)));
			if (c == '*' || c == '#') break; 
			*ipaddr++ = c;
			lcd_data(c);
		}
		if (i<=2) {
			*ipaddr++ = '.';
			lcd_data('.');
		}
	}	
	*ipaddr++ = '\0';

	while (keypad_to_ascii() != '#');
	lcd_clear_display();
	return ipaddr - ipaddr_start - 1;
}
