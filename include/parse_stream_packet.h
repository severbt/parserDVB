#include <stdint.h>

const unsigned char* find_start(const unsigned char* str);
const unsigned char* parse_packet(const unsigned char* str, const uint16_t number_pid, unsigned char** section);
