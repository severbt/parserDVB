#include <stdint.h>
#include <limits.h>

uint8_t find_end_bit(const uint16_t numBits)
{
	int endBit = numBits % CHAR_BIT;
	return endBit == 0 ? CHAR_BIT : endBit;
}


uint64_t bitmask(const uint8_t bit_count)
{
	return (((uint64_t)0x1) << bit_count) - 1;
}












	



