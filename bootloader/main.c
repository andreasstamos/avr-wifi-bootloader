#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <avr/interrupt.h>

#include "net.c"
#include <stdint.h>

#include "stage2/stage2.c"
#include "stage2_arr.c"
#include <avr/pgmspace.h>

extern int get_ip_address (char*) __attribute__ ((section (".stage2")));


void write_program_page(uint32_t page_address, uint8_t *buf, uint8_t buf_lim) {
	uint16_t b;
	uint8_t sreg_last_state;

	sreg_last_state = SREG;
	cli();

	eeprom_busy_wait();
	boot_page_erase(page_address);
	boot_spm_busy_wait();

	for (b = 0; b < buf_lim; b += 2) {
		uint16_t w = *buf++;
		w += (*buf++) << 8;
		boot_page_fill(page_address + b, w);
	}
	boot_page_write(page_address);
	boot_spm_busy_wait();
	boot_rww_enable();

	SREG = sreg_last_state;
}

int stage2(char *ipaddr) {
	int idx = 0, pa = 0x200;
	for (; pa<0x600; pa+=PAGESIZE) {
		uint8_t page[PAGESIZE];
		for (uint8_t b=0; b<PAGESIZE; ++b) page[b] = eeprom_read_byte(idx++);
		write_program_page(pa, page, sizeof(page));
	}
	for (idx = 0; idx<sizeof(stage2_bin); pa += PAGESIZE, idx += PAGESIZE) {
		write_program_page(pa, stage2_bin+idx, PAGESIZE);
	}
	//asm volatile ("call 0");
	return get_ip_address(ipaddr);
}

int main(void) {
	char ipaddr[16];
	stage2(ipaddr);

	int16_t npages = get_npages_wifi(ipaddr);
	for (int16_t page_address=0; npages>0; page_address+=PAGESIZE, --npages) {
		uint8_t page[PAGESIZE];
		get_page_wifi(ipaddr, page_address, page, sizeof(page));
		write_program_page(page_address, page, sizeof(page));
	}

	PORTB = 0;
	DDRB = 0;
	asm volatile("jmp 0");
}

