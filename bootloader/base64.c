#include <stdint.h>

uint8_t base64_inv(uint8_t c) {
	//Base64 according to RFC4648
	if ('A' <= c && c <= 'Z')	return c-'A';
	if ('a' <= c && c <= 'z')	return c-'a'+26;
	if ('0' <= c && c <= '9')	return c-'0'+52;
	if (c == '+')			return 62;
	if (c == '/')			return 63;
	return 0; //if something goes wrong, given there is no exception handling, zero seems good. (-1 would be 0xff)
		  //exception handling would increase codesize.
}

uint8_t decode(const uint8_t *enc, uint16_t enc_lim, uint8_t *dec) {
	if (enc_lim % 4 != 0) return 1;

	for (uint16_t block=0; block<enc_lim; block += 4) {
		//'=' should be ignored in base64. however it is no problem here
		//to just zero it out. (less code is produces which is better)
		uint32_t block_dec = 0;
		block_dec |= base64_inv(enc[block]);
		block_dec <<= 6;
		block_dec |= base64_inv(enc[block+1]);
		block_dec <<= 6;
		if (enc[block+2] != '=') {
			block_dec |= base64_inv(enc[block+2]);
			block_dec <<= 6;
			if (enc[block+3] != '=') {
				block_dec |= base64_inv(enc[block+3]);
			}
		}
		else block_dec <<= 6;
		*dec++ = (block_dec >> 16) & 0xff;
		if (enc[block+2] != '=') {
			*dec++ = (block_dec >> 8) & 0xff;
			if (enc[block+3] != '=') {
				*dec++ = block_dec & 0xff;
			}
		}
	}
	return 0;
}

