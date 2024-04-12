#include<avr/io.h>
#include "common/esp8266.h"
#include "base64.c"
#include <stdlib.h>
#include <string.h>

#define PAGESIZE 128
#define PAGESIZE_STR "[128]"

int16_t get_npages_wifi(uint8_t *ipaddr) {
	uint8_t url[40] = "\"http://";
	strcat(url, ipaddr);
	strcat(url, ":5000/npages\"");

	//square brackets necessary due to check in ESP8266 firmware
	static const uint8_t empty[] = PAGESIZE_STR;

	uint8_t buf[16];
	uint16_t buf_lim;

	esp8266_init();
	esp8266_command(CMD_CONNECT, 0, 0);
	esp8266_command(CMD_URL, url, sizeof(url)-1);
	esp8266_command(CMD_PAYLOAD, empty, sizeof(empty)-1);
	buf_lim = esp8266_command(CMD_TRANSMIT, buf, sizeof(buf));
	buf[buf_lim] = '\0'; 

	return atoi(buf);
}


uint8_t get_page_wifi(uint8_t *ipaddr, uint16_t page_address, uint8_t *page, uint8_t page_lim) {
       	uint8_t url[40] = "\"http://";
	strcat(url, ipaddr);
	strcat(url, ":5000/data\"");

	int8_t ret;
	uint8_t buf[((PAGESIZE*4/3)+3)/4 * 4 + 1] = "["; //Base64 has size the next multiple of 4 of the 4/3 of the initial message.
	int16_t buf_lim;

	uint8_t pa_str[10], pl_str[10];

	DDRB = 0xff;	
	esp8266_init();
	PORTB = 1;
	ret = esp8266_command(CMD_CONNECT, 0, 0);
	PORTB = 2;
	ret = esp8266_command(CMD_URL, url, sizeof(url)-1);
	PORTB = 4;
	
	//buf_lim = snprintf(buf, sizeof(buf), "[%d %d]", page_address, page_lim);
	// The below trick is to reduce code size, because with 'snprintf' it was larger than the available.
	itoa(page_address, pa_str, 10); 
	itoa(page_lim, pl_str, 10); 
	strcat(buf, pa_str);
	strcat(buf, " ");
	strcat(buf, pl_str);
	strcat(buf, "]");
	buf_lim = strlen(buf);

	//square brackets necessary due to check in ESP8266 firmware
	
	ret = esp8266_command(CMD_PAYLOAD, buf, buf_lim);
	PORTB = 8;
	buf_lim = esp8266_command(CMD_TRANSMIT, buf, sizeof(buf));
	PORTB = 16;

	decode(buf, buf_lim, page);

	return 0;
}

