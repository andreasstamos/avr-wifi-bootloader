#include <string.h>
#include "usart.h"
#include "esp8266.h"

void esp8266_init(void) {
	usart_init(103); //baud rate 9600
}

int16_t esp8266_command(uint8_t command_type, uint8_t *arg, uint16_t arg_length) {
	//returns 0 if success, 1 if fail, -1 if other error
	static uint8_t connect[] = "ESP:connect";
	static uint8_t url[] = "ESP:url:";
	static uint8_t payload[] = "ESP:payload:";
	static uint8_t transmit[] = "ESP:transmit";

	static uint8_t success[] = "\"Success\"\n";
	static uint8_t fail[] = "\"Failure\"\n";


	switch (command_type) {
		case CMD_CONNECT:
			usart_transmit_buffer(connect, sizeof(connect)-1);
			break;
		case CMD_URL:
			usart_transmit_buffer(url, sizeof(url)-1);
			usart_transmit_buffer(arg, arg_length);
			break;
		case CMD_PAYLOAD:
			usart_transmit_buffer(payload, sizeof(payload)-1);
			usart_transmit_buffer(arg, arg_length);
			break;
		case CMD_TRANSMIT:
			usart_transmit_buffer(transmit, sizeof(transmit)-1);
			break;
		default: return -1; break;
	}
	usart_transmit('\n');

	switch (command_type) {
		case CMD_CONNECT:
		case CMD_URL:
		case CMD_PAYLOAD:
			{
				uint8_t buf[50];
				uint16_t buf_lim;

				buf_lim = usart_receive_buffer(buf, sizeof(buf));
				if (!strncmp(buf, success, buf_lim)) return 0;
				else if (!strncmp(buf, fail, buf_lim)) return 1;
				break;
			}
		case CMD_TRANSMIT:
			return usart_receive_buffer(arg, arg_length);
			break;
		default:
			return -1;
			break;
	}
	return -1;
}

